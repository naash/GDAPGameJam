#include "basePhyComp.h"
#include "modelData.h"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


BasePhyComp::BasePhyComp()
{
	physicsEnabled = true;
	collided = false;
	scale = 1.0;

	rot =  new rotationalVar();
	rot->InertiaTensor = GetInertiaTensor();
	rot->MaxAngularVelocity = 180.0f;
}

BasePhyComp::~BasePhyComp()
{

}

void BasePhyComp::UpdatePhysics(float deltaTime)
{
	float mTime = 0.0f;
	if(this->physicsEnabled)
	{
	prevPosition = position;
	MovementManager::moveVerlet(deltaTime,this->position,this->velocity,this->acceleration,mTime);
	rot->angular_acceleration = glm::vec3();
	
	MovementManager::rotateVerlet1(deltaTime,rot);
	//Add Forces , Collision Detection / Response here 
	
	CheckForCollision(deltaTime);

	//To de-accelerate
	MovementManager::addForce("FRICTION",acceleration,Vector3D(), 0.95f);
	MovementManager::addForce("FRICTION",velocity,Vector3D(), 0.995f);

	if(this->shape != "complex")
		//MovementManager::addForce("GRAVITY",acceleration,Vector3D(), 0.05f);
	//Integrate Velocity
	if(!collided){
	MovementManager::setNewVelocity(deltaTime,velocity,acceleration);

	MovementManager::rotateVerlet2(deltaTime,rot);
	}
	}
}

void BasePhyComp::RegisterPhyAttributes(Vector3D p_position, glm::quat p_rotation, float p_scale)
{
	this->position = p_position;
	this->prevPosition = p_position;
	this->scale = p_scale;

	this->rot->rotation.x = p_rotation.x ;
	this->rot->rotation.y = p_rotation.y ;
	this->rot->rotation.z = p_rotation.z ;
	this->rot->rotation.w = p_rotation.w;
}

void BasePhyComp::SetModelMatrix(glm::mat4& mat)
{

	mat = glm::translate(mat, glm::vec3(position.x, position.y, position.z));

	mat *= glm::toMat4(this->rot->rotation);

	mat = glm::scale(mat, glm::vec3(scale,scale,scale));
}

void BasePhyComp::UpdatePhysicsAttrib(std::string type, Vector3D value)
{
	if(type== "VELOCITY")
	{
		this->velocity = value;
	}
	else if(type == "ACCELERATION")
	{
		this->acceleration = value;
	
	}
	else if(type == "POSITION")
	{
		this->position = value;
	}
	else if(type == "SCALE")
	{
		this->scale = value.x;
	}

}

 Vector3D BasePhyComp::GetPhysicsAttrib(std::string type)
 {
	if(type == "VELOCITY")
		return velocity;
	else if(type == "ACCELERATION")
		return acceleration;
	else if(type == "PREVPOS")
	{
		return prevPosition;
	}
	else
	{
		return position;
	}
 }

 void BasePhyComp::CheckForCollision(float dT)
 {
	std::vector<IPhysicsComp*> phyComp = mediator->fetchPhyComp();
	std::vector<ModelData*> modelComp = mediator->fetchModelComp();

	//Shape* collidingBody = new Shape();
	//Shape* objBody = new Shape();
	Shape objBody;
	Sphere objBodyS ;
	Cube objBodyC;
	if(this->shape == "sphere")
	{
		//Sphere objBodyS ;//= new Sphere();
		objBodyS.location = this->position;
		objBodyS.velocity = this->velocity;
		objBodyS.radius = this->scale /2.3;  

		//objBody = objBodyS;
	}else if(this->shape == "cube")
	{
		//Cube objBodyC;// = new Cube();
		objBodyC.location = this->position;
		objBodyC.velocity = this->velocity;

		//Loop to check index
		int i;
		for(i = 0 ; i < phyComp.size(); i++)
		{
			if(phyComp[i] == this)
			{

				break;
			}
		}

		objBodyC.min = ((BasePhyComp*)phyComp[i])->min;
		objBodyC.max = ((BasePhyComp*)phyComp[i])->max;

		////Add offset
		objBodyC.min +=objBody.location;
		objBodyC.max +=objBody.location;

		//objBody = objBodyC;
	}

	//Checking collision with other bodies (CHECKS ONLY FOR SPHERES)

	for(int i = 0 ; i < phyComp.size(); i++)
	{
		if( ((BasePhyComp*)phyComp[i])->physicsEnabled && phyComp[i] != this)
		{
			//If Object to check is a sphere type 
			if(((BasePhyComp*)phyComp[i])->shape == "sphere" && this->shape == "sphere"){

				Sphere collidingBody ;//= new Sphere();

				collidingBody.location = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");
				collidingBody.radius = 0.42f;
				Vector3D pt;
				if(Collision::SphereToSphereCollisionVelTransfer(collidingBody ,objBodyS,pt))
					{
						Vector3D vA = collidingBody.location - (((BasePhyComp*)phyComp[i])->GetPhysicsAttrib("PREVPOS"));
						Vector3D vB = this->position - this->prevPosition;

						//Rotational part.............................

						Vector3D pa =  objBodyS.location- pt;
						Vector3D pb =  collidingBody.location - pt;

						
						float lenPA = Vector3D::Magnitude(pa);
						float lenPB = Vector3D::Magnitude(pb);

						
						float t = 0.003f; // Not sure how this is relevant 
						float fractDT = t / (Vector3D::Magnitude(vA) + Vector3D::Magnitude(vB));
						//float fractDT = objBodyS.radius * ((objBodyS.radius / lenPA) - 1.0f) / Vector3D::Magnitude(objBodyS.velocity);
						fractDT = glm::clamp(fractDT, 0.0f, 1.0f);
						float revDT = (1.0f - fractDT) * dT;
						Vector3D other_acc = ((BasePhyComp*)phyComp[i])->GetPhysicsAttrib("ACCELERATION");
						Vector3D myImpulse =  ( pa * (Vector3D::DotProduct(pa, this->acceleration) /(lenPA * lenPA))) - this->acceleration;
						Vector3D otherImpulse = other_acc - pb * (Vector3D::DotProduct(pb,other_acc /(lenPB * lenPB)));

						MovementManager::rotateVerlet1(-revDT,this->rot);  //Of our Sphere 
						MovementManager::rotateVerlet1(-revDT,((BasePhyComp*)phyComp[i])->rot); //Of other Sphere
					

						//Apply impulse (Transfer of momentum, so impulse generated be other sphere will be applied on our sphere and vice versa )
						glm::vec3 imp = glm::vec3(myImpulse.x,myImpulse.y,myImpulse.z);
						glm::vec3 p = glm::vec3(pa.x,pa.y,pa.z);
						MovementManager::ApplyAngularImpulse(((BasePhyComp*)phyComp[i])->rot,imp, p);
						((BasePhyComp*)phyComp[i])->rot->angular_velocity *= 60.00f;
						
						
						imp =  glm::vec3(myImpulse.x,otherImpulse.y,otherImpulse.z);
						 p = glm::vec3(pb.x,pb.y,pb.z);
						 MovementManager::ApplyAngularImpulse(this->rot,imp, p);
						 this->rot->angular_velocity *= 60.00f;
						
						
						 //Friction between the two ............................................
						 Vector3D direcVec = this->position - collidingBody.location ; 

						 float surfaceFriction = 0.0f;

						 if ( Vector3D::DotProduct( this->velocity , collidingBody.velocity ) > 0 )   //  if sphere A is accelerating into sphere B
						 {
						 
							 surfaceFriction += Vector3D::Magnitude(this->velocity * (Vector3D::DotProduct(this->velocity,direcVec) / Vector3D::Magnitude(this->velocity)));
						 }

						 	 if ( Vector3D::DotProduct( this->velocity , collidingBody.velocity ) < 0 )   //  if sphere A is accelerating into sphere B
						 {
						 
							 surfaceFriction += Vector3D::Magnitude(collidingBody.velocity * (Vector3D::DotProduct(collidingBody.velocity,direcVec) / Vector3D::Magnitude(collidingBody.velocity)));
						 }

						 MovementManager::ApplyForceAtPoint(this->rot, -imp * surfaceFriction, -p); //To add friction
						 MovementManager::ApplyForceAtPoint(((BasePhyComp*)phyComp[i])->rot, imp * surfaceFriction, p); //To add friction
						
						 //......................................................................
						 
						 MovementManager::rotateVerlet1(revDT,this->rot);
						 MovementManager::rotateVerlet1(revDT,((BasePhyComp*)phyComp[i])->rot);
					

						 
						this->position = objBodyS.location;
						this->velocity = objBodyS.velocity;

						//...........................................
							((BasePhyComp*)phyComp[i])->UpdatePhysicsAttrib("POSITION",collidingBody.location);
							((BasePhyComp*)phyComp[i])->UpdatePhysicsAttrib("VELOCITY",collidingBody.velocity);
							((BasePhyComp*)phyComp[i])->collided = true;
						
					}
				else
				{
				((BasePhyComp*)phyComp[i])->collided = false;
				}
					

			}
			else if(((BasePhyComp*)phyComp[i])->shape == "cube"  && this->shape == "sphere")
			{
				Cube collidingBody;// = new Cube();
				collidingBody.location  = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");

				collidingBody.min = ((BasePhyComp*)phyComp[i])->min;
				collidingBody.max = ((BasePhyComp*)phyComp[i])->max;

				//Add offset
				collidingBody.min += collidingBody.location;
				collidingBody.max += collidingBody.location;

				if(Collision::CubeToSphereCollision(collidingBody,objBodyS))
					{
						//std::cout<<"Collision"<<std::endl;
						this->position = objBody.location;
						
					}

			}else if(((BasePhyComp*)phyComp[i])->shape == "complex"  && this->shape == "sphere")
			{
				Shape collidingBody;
				collidingBody.location  = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");
				Vector3D pt;
				if(Collision::MeshToSphereCollision(collidingBody ,objBodyS,modelComp[i],pt))
					{
						Vector3D pa =  objBodyS.location- pt;
						float lenPA = Vector3D::Magnitude(pa);


						//............................
						float vel = Vector3D::Magnitude(this->velocity);
						//Rotational Stuff here
						float fractDT = objBodyS.radius * ((objBodyS.radius / lenPA) - 1.0f) / vel;
							float partialDT = (1.f - fractDT) * dT;
							MovementManager::rotateVerlet1(-partialDT,this->rot);
							
							Vector3D myImpulse =  ( pa * (Vector3D::DotProduct(pa, this->velocity) /(lenPA * lenPA))) - this->velocity;
							glm::vec3 imp = glm::vec3(myImpulse.x,myImpulse.y,myImpulse.z);
							glm::vec3 p = glm::vec3(pa.x,pa.y,pa.z);
							MovementManager::ApplyAngularImpulse(this->rot, imp * 2.0f, p);
					
							
							//Friction stuff here 
							
							//Projecting acc on surface normal 
							Vector3D friction = -this->acceleration * (Vector3D::DotProduct(this->acceleration,collidingBody.normalVec) / Vector3D::Magnitude(this->acceleration));

							imp = glm::vec3(friction.x, friction.y, friction.z);

							MovementManager::ApplyForceAtPoint(this->rot,imp  , p); //To add friction
							//.......................
							
							
						
							MovementManager::rotateVerlet1(partialDT,this->rot);
		
						//.....................
						this->position = objBodyS.location;
						this->velocity = objBodyS.velocity;

					}
			}
			
		}
	}
 }
	


 glm::mat3 BasePhyComp::GetInertiaTensor()
 {
	 if(this->shape == "sphere")
	 {


		 return glm::mat3((2.f / 5.f) * scale * (scale/2));
	
	 }else if(shape == "cube")
	 {
	 
	  glm::vec3 HalfWidths(0.5f, 0.5f, 0.5f);
	 float x2 = HalfWidths.x * 2.f; x2 *= x2;
		float y2 = HalfWidths.y * 2.f; y2 *= y2;
		float z2 = HalfWidths.z * 2.f; z2 *= z2;

		float ixx = (1.f / 12.f) * scale * (y2 + z2);
		float iyy = (1.f / 12.f) * scale * (x2 + z2);
		float izz = (1.f / 12.f) * scale * (x2 + y2);

		glm::mat3 tensor(1.f);

		tensor[0][0] = ixx;
		tensor[1][1] = iyy;
		tensor[2][2] = izz;
		
		return tensor;
	 
	 }else
	 {
	 	return glm::mat3(1.0f);  // this kind of shape should always be fixed
	 }
 
 
 
 }

 std::string BasePhyComp::getType()
 {
	return "BASE";
 }

 bool BasePhyComp::isColliding()
 {
	return false; //Only havok handles collisions
 }