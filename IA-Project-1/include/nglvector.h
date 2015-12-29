/**
  *@file nglVector.h
  *@date 20020625
  *Aquí definimos las clases de vectores y matrices que se pueden utilizar.
  *Se puede usar la nomenglatura de Cg o del lenguaje de shaders de OGL2.
  *@todo Matrices y operaciones matriciales
  */
#ifndef __NGL_VECTOR_H__
#define __NGL_VECTOR_H__

#include <stdio.h>
#include <math.h>

/**
  *@author Alejandro Domingo Monge
  *@description Vector de dos componentes
  */
class  Vector2D {
public:
	float x;
	float y;

	/// operador suma
	Vector2D operator +(const Vector2D v);
	/// operador resta
	Vector2D operator -(const Vector2D v);
	/// operador producto escalar
	float operator *(const Vector2D v);
	/// producto componente a componente por f
	Vector2D operator *(const float f);
	float operator [](int i);

	/// la longitud del vector
	float length(void);

	/// la norma
	float norm(void);
	/// normaliza el vector y 
	float normalize(void);

	/// constructor
	Vector2D(float _x = 0.0f, float _y = 0.0f);
};

/**
  *@author Alejandro Domingo Monge
  *Vector de tres componentes
  */
class  Vector3D {
public:
	union {
		float x;
		float r;
	};
	union {
		float y;
		float g;
	};
	union {
		float z;
		float b;
	};

	/// operador suma
	Vector3D operator +(const Vector3D v);
	/// operador resta
	Vector3D operator -(const Vector3D v);
	/// operador producto escalar
	float operator *(const Vector3D v);
	/// producto componente a componente por f
	Vector3D operator *(const float f);
	friend Vector3D operator*(float s, const Vector3D v);

	Vector3D operator ^(const Vector3D v);
	float operator [](int i);

	/// longitud
	float length(void);
	/// la norma
	float norm(void);
	/// normaliza el vector
	///@return longitud del vector antes de normalizarlo
	float normalize(void);

	Vector3D(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
#endif // __NGL_VECTOR_H__



