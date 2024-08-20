#include "Vector3D.h"

#include <math.h>


Vector3D::Vector3D( float x, float y, float z )
{
	this->x = x; this->y = y; this->z = z;
	return;
}

Vector3D::Vector3D( const Vector3D &v )
{
	this->x = v.x; this->y = v.y; this->z = v.z;
	return;
}

bool Vector3D::operator ==(const Vector3D &v) const
{
	if((abs(this->x - v.x) < 0.0001)
	&&	(abs(this->y - v.y) < 0.0001)
	&& (abs(this->z - v.z) < 0.0001))
	{
		return true;
	}else{
		return false;
	}
}

bool Vector3D::operator> (const Vector3D &v) 
{
	if((this->x > v.x)
		&&(this->y > v.y)
		&&(this->z > v.z))
	{
		return true;
	}else{
		return false;
	}
}

bool Vector3D::operator< (const Vector3D &v)
{
	if((this->x < v.x)
		&&(this->y < v.y)
		&&(this->z < v.z))
	{
		return true;
	}else{
		return false;
	}
}


Vector3D& Vector3D::operator=(const Vector3D &v)
{
	// Check for self-assignment *IMPORTANT*
	if ( this == &v )	return *this;
	// Else...copy values
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D &v)
{
	Vector3D result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return result;
}

Vector3D Vector3D::operator-(const Vector3D &v)
{
	Vector3D result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

Vector3D& Vector3D::operator+=(const Vector3D &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}
//Scaler multiplication
Vector3D Vector3D::operator*(float scalar)
{
	Vector3D result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	result.z = this->z * scalar;
	return result;
}

//Scaler divide
Vector3D Vector3D::operator/(float scalar)
{
	Vector3D result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	result.z = this->z / scalar;
	return result;
}


//Scaler substract
Vector3D Vector3D::operator-(float scalar)
{
	Vector3D result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	result.z = this->z - scalar;
	return result;
}

// Times a scalar
Vector3D& Vector3D::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

// Divided by a scalar
Vector3D& Vector3D::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}
	
Vector3D Vector3D::operator-()	// Negative on all directions
{
	return Vector3D( -x, -y, -z );
}

/*static*/ // Subtracts one vector from another and returns in Sub (by reference)
void Vector3D::Subtract(const float &x0, const float &y0, const float &z0, 
                       const float &x1, const float &y1, const float &z1,
                       float &xSub, float &ySub, float &zSub)
{
	xSub = x0 - x1; ySub = y0 - y1; zSub = z0 - z1;
	return;
}

/*static*/ // Subtracts one vector from another and returns in Sub (by reference)
void Vector3D::Subtract( const Vector3D &v1, const Vector3D &v2, Vector3D &vSub )
{
	Vector3D::Subtract( v1.x, v1.y, v1.z, 
		               v2.x, v2.y, v2.z, 
					   vSub.x, vSub.y, vSub.z );
	return;
}

/*static*/ // Subtracts returns one vector from another 
Vector3D Vector3D::Subtract( const Vector3D &v1, const Vector3D &v2 )
{
	Vector3D vTemp;
	Vector3D::Subtract( v1, v2, vTemp );
	return vTemp;
}

/*static*/
Vector3D Vector3D::ScalarMultiply( const Vector3D &v, float s)
{
	Vector3D vTemp(v);
	vTemp *= s;
	return vTemp;
}

/*static*/
Vector3D Vector3D::ScalarDivide( const Vector3D &v, float s)
{
	Vector3D vTemp(v);
	vTemp /= s;
	return vTemp;
}

/*static*/
// Takes cross of vec0 (x0, y0, z0) and vec1 (x1, y1, z1) and 
//	returns cross (xCross, yCross, zCross)
void Vector3D::CrossProduct( const float &x0, const float &y0, const float &z0, 
                            const float &x1, const float &y1, const float &z1,
                            float &xCross, float &yCross, float &zCross)
{
    /* find cross-product between these vectors */
    xCross = y0 * z1 - z0 * y1;
    yCross = z0 * x1 - x0 * z1;
    zCross = x0 * y1 - y0 * x1;
	return;
}

/*static*/
Vector3D Vector3D::CrossProduct( const Vector3D &v1, const Vector3D &v2 )
{
	Vector3D vCross;

	Vector3D::CrossProduct( v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, vCross.x, vCross.y, vCross.z );
	return  vCross;
}

/*static*/
float Vector3D::DotProduct( const float &x1, const float &y1, const float &z1, 
                           const float &x2, const float &y2, const float &z2 )
{
	float dot = x1 * x2 + y1 * y2 + z1 * z2;
	return dot;
}

/*static*/
float Vector3D::DotProduct( const Vector3D &v1, const Vector3D &v2 )
{
	return DotProduct( v1.x, v1.y, v1.z, v2.x, v2.y, v2.z );
}

/*static*/	
// Set vector to unit size (length of 1.0)
void Vector3D::Normalize( float &x, float &y, float &z)
{
	// Convert to double so there is no loss...
	double x2 = static_cast<double>(x) * static_cast<double>(x);
	double y2 = static_cast<double>(y) * static_cast<double>(y);
	double z2 = static_cast<double>(z) * static_cast<double>(z);
	double length = x2 + y2 + z2;
	if ( length == 0 )
	{
		x = y = z = 0.0f;
	} 
	else
	{	// Multiply by reciprical as multiplies are faster than divides (usually)
		double reciprical = 1 / sqrt( length );
		x = static_cast<float>( static_cast<double>(x) * reciprical   );
		y = static_cast<float>( static_cast<double>(y) * reciprical  );
		z = static_cast<float>( static_cast<double>(z) * reciprical  );
	}
	return;
}

/*static*/	
void Vector3D::Normalize( Vector3D &v )
{
	Vector3D::Normalize( v.x, v.y, v.z );
	return;
}

void Vector3D::Normalize(void)
{
	Vector3D::Normalize( *this );
	return;
}

/*static*/
float Vector3D::Magnitude( const Vector3D &v )
{
	return static_cast<float>(sqrt( v.x*v.x + v.y*v.y + v.z*v.z ));
}

float Vector3D::Magnitude( void )
{
	return Vector3D::Magnitude( *this );
}
/*static*/
// Same as magnatude, but without the square root...
float Vector3D::MagnitudeSquared( const Vector3D &v )
{
	return static_cast<float>( v.x*v.x + v.y*v.y + v.z*v.z );

}

float Vector3D::MagnitudeSquared( void )
{
	return Vector3D::Magnitude( *this );
}

/*static*/
float Vector3D::Distance( const Vector3D &v1, const Vector3D &v2)
{
	double deltaX = static_cast<double>( v1.x - v2.x );
	double deltaY = static_cast<double>( v1.y - v2.y );
	double deltaZ = static_cast<double>( v1.z - v2.z );
	return static_cast<float>(sqrt( deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ ));
}

/*static*/
// Same as distance, but without the square root...
float Vector3D::DistanceSquared( const Vector3D &v1, const Vector3D &v2)
{
	double deltaX = static_cast<double>( v1.x - v2.x );
	double deltaY = static_cast<double>( v1.y - v2.y );
	double deltaZ = static_cast<double>( v1.z - v2.z );
	return static_cast<float>( deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );
}

void Vector3D::Reverse(void)
{
	this->x = -(this->x);
	this->y = -(this->y);
	this->z = -(this->z);
	return;
}