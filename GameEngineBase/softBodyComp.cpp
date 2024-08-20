#include "softBodyComp.h"



SoftBodyPhyComp::SoftBodyPhyComp()
	: mTime(0.0f), mK(20.6f), mDamping(0.99f), mGravity(0.0f, -0.5f, 0.0f),  mMass(1.0f), mWind(0.0f, 0.0f, 0.5f)
{
	shape = "softBody";
}

SoftBodyPhyComp::~SoftBodyPhyComp()
{

}



void SoftBodyPhyComp::UpdatePhysics( float dt )
{
	
	unsigned int numNodes = mNodes.size();
	float mTime = 0.0f; 
	for (unsigned int idxNode = 0; idxNode < numNodes; idxNode++)
	{
		if (mNodes[idxNode]->FixedPosition) continue;
		sNode* node = mNodes[idxNode];
		
		MovementManager::moveVerlet(dt,node->Position,node->Velocity,node->Acceleration, mTime);

	}
	// calculate a(t + h)
	
	CheckForCollision();
	CalculateSpringForces();
	// step 3: v(t + h) = v(t + h/2) + (h/2)*a(t + h)
	for (unsigned int idxNode = 0; idxNode < numNodes; idxNode++)
	{
		if (mNodes[idxNode]->FixedPosition && mNodes[idxNode]->collided) continue;
		sNode* node = mNodes[idxNode];
		MovementManager::setNewVelocity(dt/2,node->Velocity,node->Acceleration);
		
	}

	//Call Base Class method
	MovementManager::moveVerlet(dt,this->position,this->velocity,this->acceleration,mTime);
	//Add Forces , Collision Detection / Response here 
	MovementManager::addForce("FRICTION",acceleration,Vector3D(), 0.95f);
	MovementManager::addForce("FRICTION",velocity,Vector3D(), 0.995f);

	//Integrate Velocity
	MovementManager::setNewVelocity(dt,velocity,acceleration);
	
}

void SoftBodyPhyComp::SetNodeFixed( unsigned int idx, bool value )
{
	mNodes[idx]->FixedPosition = value;
}

void SoftBodyPhyComp::CalculateSpringForces()
{
	// clear the existing spring forces
	std::vector<sNode*>::iterator itNode = mNodes.begin();
	while (itNode != mNodes.end())
	{
		(*itNode)->SpringForce = Vector3D();
		itNode++;
	}
	// sum up the spring forces in the nodes
	std::vector<sSpring*>::iterator itSpring = mSprings.begin();
	while (itSpring != mSprings.end())
	{
		Vector3D vec = (*itSpring)->NodeB->Position - (*itSpring)->NodeA->Position;
		float len =  glm::length(glm::vec3(vec.x,vec.y,vec.z));//Vector3D::Magnitude(vec);
		vec /= len;

		vec *= mK * (len - (*itSpring)->RestLength);

		(*itSpring)->NodeA->SpringForce += vec;
		(*itSpring)->NodeB->SpringForce -= vec;

		itSpring++;
	}

	float windFactor = 1.0f + 0.4f * glm::sin(mTime);
	Vector3D accWind = mWind * windFactor;
	//std::stringstream ss;
	//ss << windFactor;
	//std::cout << ss.str() << std::endl;
	
	// calculate the damping and wind factors, then assign the Acceleration
	unsigned int numVerts = mNodes.size();
	for (unsigned int idxVert = 0; idxVert < numVerts; idxVert++)
	{
		if(mNodes[idxVert]->collided)
		{
			mNodes[idxVert]->Velocity = Vector3D();
			mNodes[idxVert]->Acceleration = Vector3D();
		}else{
		Vector3D accSpring = mNodes[idxVert]->SpringForce / mMass;
		Vector3D accDamping = mNodes[idxVert]->Velocity * mDamping;
		mNodes[idxVert]->Acceleration = mGravity+  accWind + accSpring - accDamping;
		}
	}
}

void SoftBodyPhyComp::SetSpringLengths()
{
	std::vector<sSpring*>::iterator itSpring = mSprings.begin();
	while (itSpring != mSprings.end())
	{
		(*itSpring)->Length = Vector3D::Magnitude((*itSpring)->NodeA->Position - (*itSpring)->NodeB->Position);
		itSpring++;
	}
}

void SoftBodyPhyComp::AddSpring( unsigned int idxA, unsigned int idxB )
{
	sNode* nodeA = mNodes[idxA];
	sNode* nodeB = mNodes[idxB];

	std::map<unsigned int, sSpring*>::iterator itSpring;

	sSpring* springFromA = new sSpring();
	sSpring* springFromB = new sSpring();
	bool springAfound = false;
	bool springBfound = false;
	itSpring = nodeA->Springs.find(idxB);
	if (itSpring != nodeA->Springs.end())
	{
		springFromA = itSpring->second;
		springAfound = true;
	}

	itSpring = nodeB->Springs.find(idxA);
	if (itSpring != nodeB->Springs.end())
	{
		springFromB = itSpring->second;
		springBfound = true;
	}

	if (springAfound)
	{
		if (springBfound)
		{
			return;
		}
		nodeB->Springs[idxA] = springFromA;
	}
	else if (springBfound)
	{
		nodeA->Springs[idxB] = springFromB;
	}
	else
	{
		float len = Vector3D::Magnitude(mNodes[idxA]->Position - mNodes[idxB]->Position);
		sSpring* spring(new sSpring(nodeA, nodeB, len));
		nodeA->Springs[idxB] = spring;
		nodeB->Springs[idxA] = spring;
		mSprings.push_back(spring);
	}

	
}

void SoftBodyPhyComp::SetSpringsFromTriangulatedIndices( const std::vector<unsigned int>& indices )
{
	unsigned int numIndices = indices.size();
	for (unsigned int idxIndex = 0; idxIndex < numIndices; idxIndex += 3)
	{
		unsigned int idxA = indices[idxIndex];
		unsigned int idxB = indices[idxIndex + 1];
		unsigned int idxC = indices[idxIndex + 2];
		AddSpring(idxA, idxB);
		AddSpring(idxB, idxC);
		AddSpring(idxC, idxA);
	}
}

void SoftBodyPhyComp::SetVertices( const std::vector<PLYVERTEX>& vertices, float radius )
{
	if (!mNodes.empty())
	{
		throw std::exception("woah woah woah... they've been set");
	}

	//Check shortest distance between vertices
	float dist = 99.0f;
	
	for(int i = 0; i < vertices.size() - 1; i++)
	{
		for(int j = i+1; j < vertices.size(); j++)
		{
			Vector3D pos1 = vertices[i].pos;
			Vector3D pos2 = vertices[j].pos;

			if(dist > Vector3D::Magnitude(pos1 - pos2))
			{
				dist = Vector3D::Magnitude(pos1 - pos2);
			}
	
		}
	
	}


	dist/=4;

	
	if(radius < dist)
		mRadius = radius;
	else
		mRadius = dist;

	mNodes.resize(vertices.size());
	unsigned int numNodes = vertices.size();
	for (unsigned int idx = 0; idx < numNodes; idx++)
	{
		const PLYVERTEX* v = &vertices[idx];
		sNode* node = new sNode(idx, v->pos.x, v->pos.y,v->pos.z);
		node->collided =false;
		mNodes[idx] = node;
	}
}

void SoftBodyPhyComp::GetPosition( unsigned int idx, CVertex_fXYZW &floatXYZ )
{
	sNode* node = mNodes[idx];
	floatXYZ.x = node->Position.x;
	floatXYZ.y = node->Position.y;
	floatXYZ.z = node->Position.z;
}


std::vector<sNode*> SoftBodyPhyComp::GetNodeList()
{
	return mNodes;
}
//(indices.size()/2)
void SoftBodyPhyComp::ComputeSprings(const std::vector<PLYELEMENT>& indices,float offset)
{
	for (int indicesCnt = 0; indicesCnt < indices.size() - offset; indicesCnt++)
	{
		
		unsigned int idxA = indices[indicesCnt].vertex_1;// (idxRow * numNodesHoriz) + idxCol;
		unsigned int idxB = indices[indicesCnt].vertex_2;
		unsigned int idxC =  indices[indicesCnt+offset].vertex_1;
		unsigned int idxD =  indices[indicesCnt+offset].vertex_2;



			this->AddSpring(idxA, idxB);
			this->AddSpring(idxA, idxC);
			this->AddSpring(idxA, idxD);
			this->AddSpring(idxC, idxB);
			this->AddSpring(idxC, idxD);
			this->AddSpring(idxB, idxD);
		
	}
}

void SoftBodyPhyComp::SetSpringConst(float p_mk)
{

	mK = p_mk;
}

 void SoftBodyPhyComp::CheckForCollision()
 {
	std::vector<IPhysicsComp*> phyComp = mediator->fetchPhyComp();
	std::vector<ModelData*> modelComp = mediator->fetchModelComp();

	
	//Shape collidingBody ;//= new Shape();
	Sphere nodeSphere ;//= new Sphere();






	Vector3D pt;
	//	Checking collision with other Nodes
	for(std::vector<sNode*>::iterator snodeOuter = mNodes.begin(); snodeOuter != mNodes.end() ; snodeOuter++ )
	{
				Sphere collidingBody; //;= new Sphere();

				collidingBody.location = (*snodeOuter)->Position;
				collidingBody.velocity = (*snodeOuter)->Velocity;
			    collidingBody.radius = mRadius;
				collidingBody.location += this->position;
				for(std::vector<sNode*>::iterator snodeInner = snodeOuter+1; snodeInner != mNodes.end() ; snodeInner++ )
				{
					nodeSphere.location = (*snodeInner)->Position;
					nodeSphere.velocity = (*snodeInner)->Velocity;
					nodeSphere.radius = mRadius;
					nodeSphere.location += this->position;
					if(Collision::SphereToSphereCollisionVelTransfer(nodeSphere, collidingBody, pt))
					{
						//std::cout<<"Collision with itself"<<std::endl;
						//(*snodeOuter)->Position = nodeSphere->location;
							Vector3D::Normalize(collidingBody.velocity);
						(*snodeOuter)->Velocity = collidingBody.velocity;
							Vector3D::Normalize(nodeSphere.velocity);
						(*snodeInner)->Velocity = nodeSphere.velocity;

						//(*snodeOuter)->collided = true;
					}
					else
					{
						//(*snodeOuter)->collided = false;
					}
	
				}

	}



	//Checking collision with other bodies
	for(int i = 0 ; i < phyComp.size(); i++)
	{  
	
		if( ((BasePhyComp*)phyComp[i])->physicsEnabled && phyComp[i] != this)
		{
			//If Object to check is a sphere type 
			if(((BasePhyComp*)phyComp[i])->shape == "sphere"){

				Sphere collidingBody;// = new Sphere();

				collidingBody.location = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");
				(collidingBody).radius = 0.5f;
				Vector3D velSum;
				Vector3D posSum;
				bool collided = false;
				for(std::vector<sNode*>::iterator snode = mNodes.begin(); snode != mNodes.end() ; snode++ )
				{
					nodeSphere.location = (*snode)->Position;
					nodeSphere.velocity = (*snode)->Velocity;
					nodeSphere.radius = mRadius*4;

					nodeSphere.location += this->position;
					
					if(Collision::SphereToSphereCollisionVelTransfer((collidingBody) ,nodeSphere,pt))
					{
						
						nodeSphere.location -= this->position;
						(*snode)->Position = nodeSphere.location;
						Vector3D::Normalize(nodeSphere.velocity);
						(*snode)->Velocity = nodeSphere.velocity;


						//collidingBody->velocity *= 4.0f;
						Vector3D::Normalize(collidingBody.velocity);
						velSum += collidingBody.velocity;
						posSum += collidingBody.location;
						//phyComp[i]->UpdatePhysicsAttrib("ACCELERATION",collidingBody->velocity);
						//((BasePhyComp*)phyComp[i])->collided = true;
						(*snode)->collided = true;
						collided =true;
					}
					else
					{
						(*snode)->collided = false;
					}
	
				}
				if(collided){
				
				velSum/= mNodes.size(); 
				posSum/= mNodes.size(); 
						//phyComp[i]->UpdatePhysicsAttrib("POSITION",posSum);
						Vector3D oldVel = phyComp[i]->GetPhysicsAttrib("VELOCITY");
						Vector3D newVel = Vector3D::CrossProduct(oldVel,velSum);
						newVel = oldVel- velSum;
						newVel = velSum -oldVel;
						//phyComp[i]->UpdatePhysicsAttrib("VELOCITY",Vector3D(0.5f,0.0f,0.0f));
						//phyComp[i]->UpdatePhysicsAttrib("ACCELERATION",Vector3D(velSum));
				}
				
			}
			else if(((BasePhyComp*)phyComp[i])->shape == "cube")
			{

				Cube collidingBody;// = new Cube();

				collidingBody.location  = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");

				(collidingBody).min = ((BasePhyComp*)phyComp[i])->min;
				(collidingBody).max = ((BasePhyComp*)phyComp[i])->max;

				//Add offset
				(collidingBody).min +=(collidingBody).location;
				(collidingBody).max +=(collidingBody).location;

				for(std::vector<sNode*>::iterator snode = mNodes.begin(); snode != mNodes.end() ; snode++ )
				{
					nodeSphere.location = (*snode)->Position;
					nodeSphere.velocity = (*snode)->Velocity;
					nodeSphere.radius = mRadius;
					nodeSphere.location += this->position;
					if(Collision::CubeToSphereCollision((collidingBody) ,nodeSphere))
					{
						//std::cout<<"Collision1"<<std::endl;
						nodeSphere.location -= this->position;

						(*snode)->Position = nodeSphere.location;
						Vector3D::Normalize(collidingBody.velocity);
						(*snode)->Velocity = collidingBody.velocity;
						(*snode)->collided = true;
					}
					else
					{
						(*snode)->collided = false;
					}
	
				}
			
			
			
			}else if(((BasePhyComp*)phyComp[i])->shape == "complex")
			{
				Shape collidingBody;
				collidingBody.location  = phyComp[i]->GetPhysicsAttrib("POSITION");
				collidingBody.velocity = phyComp[i]->GetPhysicsAttrib("VELOCITY");

				for(std::vector<sNode*>::iterator snode = mNodes.begin(); snode != mNodes.end() ; snode++ )
				{
					nodeSphere.location = (*snode)->Position;
					nodeSphere.velocity = (*snode)->Velocity;
					nodeSphere.radius = mRadius;
					nodeSphere.location += this->position;
					Vector3D pt;
					if(Collision::MeshToSphereCollision(collidingBody ,nodeSphere,modelComp[i],pt))
					{
						//std::cout<<"CollisionMesh"<<std::endl;
						nodeSphere.location -= this->position;
						//this->position =  nodeSphere->location;
						(*snode)->Position = nodeSphere.location;
						Vector3D::Normalize(nodeSphere.velocity);
						(*snode)->Velocity = nodeSphere.velocity;
						//this->velocity = nodeSphere->velocity;
						(*snode)->collided = true;
					}
					else
					{
						(*snode)->collided = false;
					}
				
				}
			}else if(((BasePhyComp*)phyComp[i])->shape == "softBody")
			{
				std::vector<sNode*> otherNodes = ((SoftBodyPhyComp*)phyComp[i])->GetNodeList();
				for(int k = 0;
					k < (otherNodes.size()) ; k++ )
				{
					Sphere collidingBody;
					collidingBody.location = (otherNodes[k])->Position;
					collidingBody.velocity = (otherNodes[k])->Velocity;
					(collidingBody).radius = ((SoftBodyPhyComp*)phyComp[i])->mRadius*4;
					collidingBody.location += ((SoftBodyPhyComp*)phyComp[i])->GetPhysicsAttrib("POSITION");
					Sphere nodeSphere;// = new Sphere();
					for(std::vector<sNode*>::iterator snode = mNodes.begin(); snode != mNodes.end() ; snode++ )
					{
						
						nodeSphere.location = (*snode)->Position;
						nodeSphere.velocity = (*snode)->Velocity;
						nodeSphere.radius = mRadius*4;
						nodeSphere.location += this->position;

						if(Collision::SphereToSphereCollisionVelTransfer(collidingBody ,nodeSphere,pt))
						{
							//std::cout<<"Collision"<<std::endl;
							nodeSphere.location -= this->position;
							(*snode)->Position = nodeSphere.location;
							Vector3D::Normalize(nodeSphere.velocity);
							(*snode)->Velocity = nodeSphere.velocity;
							(*snode)->collided = true;
						}
						else
						{
							(*snode)->collided = false;
						}
	
					}

	
				
			}


		}
		}
	}
	
	
 }