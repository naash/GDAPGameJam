#ifndef _Vector3D_GH
#define _Vector3D_GH



class Vector3D
{
public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {};
	Vector3D( float x, float y, float z );
	Vector3D( const Vector3D &v );	// Copy constructor
	~Vector3D() {};
	float x; float y; float z;

	// These are used on vector types
	bool operator==(const Vector3D &v) const; //Equals
	Vector3D& operator=(const Vector3D &v); //Assignmnet
	Vector3D operator+(const Vector3D &v); //Vector Addition
	Vector3D operator-(const Vector3D &v); //Vector Subtraction
	Vector3D& operator+=(const Vector3D &v); 
	Vector3D& operator-=(const Vector3D &v);
	Vector3D operator*(float scaler); // Scaler multiplication
	Vector3D operator/(float scaler); //Scaler divide
	Vector3D operator-(float scaler); //Scaler substraction
	Vector3D& operator*=(float scalar);	// Times a scalar
	Vector3D& operator/=(float scalar);	// Divided by a scalar
	Vector3D operator-();	// Negative on all directions
    //Comparison 
	bool operator< (const Vector3D &v);
	bool operator> (const Vector3D &v);
	
	// Helpful functions
	void Normalize(void);
	float Magnitude(void);
	float MagnitudeSquared(void);
	void Reverse(void);
	
	// Helpful static functions...
	static void Normalize( float &x, float &y, float &z);
	static void Normalize( Vector3D &v );
	static float Magnitude( const Vector3D &v );
	static float MagnitudeSquared( const Vector3D &v );
	static float Distance( const Vector3D &v1, const Vector3D &v2);
	static float DistanceSquared( const Vector3D &v1, const Vector3D &v2);

	static void Subtract( const float &x0, const float &y0, const float &z0, 
                          const float &x1, const float &y1, const float &z1,
                          float &xSub, float &ySub, float &zSub);
	static void Subtract( const Vector3D &v1, const Vector3D &v2, Vector3D &vSub );
	static Vector3D Subtract( const Vector3D &v1, const Vector3D &v2 );
	static Vector3D ScalarMultiply( const Vector3D &v, float s);
	static Vector3D ScalarDivide( const Vector3D &v, float s);

	static void CrossProduct( const float &x0, const float &y0, const float &z0, 
	                          const float &x1, const float &y1, const float &z1,
	                          float &xCross, float &yCross, float &zCross);
	

	static Vector3D CrossProduct( const Vector3D &v1, const Vector3D &v2 );

	static float DotProduct( const float &x1, const float &y1, const float &z1, 
	                         const float &x2, const float &y2, const float &z2 );
	static float DotProduct( const Vector3D &v1, const Vector3D &v2 );

	void NormalizeVector();

	

};

#endif