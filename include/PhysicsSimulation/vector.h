// vector.h
// Visualização 3D
// W. Celes - celes@inf.puc-rio.br
// PUC-Rio, Jan 2008

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <math.h>

struct Vector2
{
	float x, y;

	Vector2 ()
	{
	}

	Vector2 (float vx, float vy)
		: x(vx), y(vy)
	{
	}
	void Set (float vx, float vy)
	{
		x = vx; y = vy;
	}

	float SqrLength () const
	{
		return (x*x+y*y);
	}

	float Length () const
	{
		return (float)sqrt(x*x+y*y);
	}

	float Normalize ()
	{
		float l = Length();
		if (l != 0.0f)
		{
			float d = 1.0f/l;
			x *= d; y *= d;
		}
		return l;
	}

	Vector2& operator+= (const Vector2& other)
	{
		x += other.x; y += other.y;
		return *this;
	}

	Vector2& operator+= (float scalar)
	{
		x += scalar; y += scalar;
		return *this;
	}

	Vector2& operator-= (const Vector2& other)
	{
		x -= other.x; y -= other.y;
		return *this;
	}

	Vector2& operator-= (float scalar)
	{
		x -= scalar; y -= scalar;
		return *this;
	}

	Vector2 operator- ()
	{
		Vector2 v(-x,-y);
		return v;
	}

	Vector2& operator*= (const Vector2& other)
	{
		x *= other.x; y *= other.y;
		return *this;
	}

	Vector2& operator*= (float scalar)
	{
		x *= scalar; y *= scalar;
		return *this;
	}

	Vector2& operator/= (float scalar)
	{
		x /= scalar; y /= scalar;
		return *this;
	}

	friend float Dot (const Vector2& a, const Vector2& b)
	{
		return a.x*b.x + a.y*b.y;
	}

	void Print (const char* label=0) const
	{
		printf("%s: %g  %g\n", label ? label : "", x, y);
	}

};

struct Vector3
{
	float x, y, z;

	Vector3 ()
	{
	}

	Vector3 (float vx, float vy, float vz)
		: x(vx), y(vy), z(vz)
	{
	}
	void Set (float vx, float vy, float vz)
	{
		x = vx; y = vy; z = vz;
	}

	float SqrLength () const
	{
		return (x*x+y*y+z*z);
	}

	float Length () const
	{
		return (float)sqrt(x*x+y*y+z*z);
	}

	float Normalize ()
	{
		float l = Length();
		if (l != 0.0f)
		{
			float d = 1.0f/l;
			x *= d; y *= d; z *= d;
		}
		return l;
	}

	Vector3& operator+= (const Vector3& other)
	{
		x += other.x; y += other.y; z += other.z;
		return *this;
	}

	Vector3& operator+= (float scalar)
	{
		x += scalar; y += scalar; z += scalar;
		return *this;
	}

	Vector3& operator-= (const Vector3& other)
	{
		x -= other.x; y -= other.y; z -= other.z;
		return *this;
	}

	Vector3& operator-= (float scalar)
	{
		x -= scalar; y -= scalar; z -= scalar;
		return *this;
	}

	Vector3 operator- ()
	{
		Vector3 v(-x,-y,-z);
		return v;
	}

	Vector3& operator*= (const Vector3& other)
	{
		x *= other.x; y *= other.y; z *= other.z;
		return *this;
	}

	Vector3& operator*= (float scalar)
	{
		x *= scalar; y *= scalar; z *= scalar;
		return *this;
	}

	Vector3& operator/= (float scalar)
	{
		x /= scalar; y /= scalar; z /= scalar;
		return *this;
	}

	friend float Dot (const Vector3& a, const Vector3& b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	friend Vector3 Cross (const Vector3& a, const Vector3& b)
	{
		return Vector3(a.y*b.z-b.y*a.z,b.x*a.z-a.x*b.z,a.x*b.y-b.x*a.y);
	}

	void Print (const char* label=0) const
	{
		printf("%s: %g  %g  %g\n", label ? label : "", x, y, z);
	}

};

#endif
