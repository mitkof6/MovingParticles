#ifndef QUATERNION_H
#define QUATERNION_H

#ifdef _WIN32
#define M_PI 3.14f
#endif

#include <iostream>
#include <math.h>
#include "Matrices.h"


class Quaternion {
	float mData[4];

public:

	Quaternion() {
		mData[0] = mData[1] = mData[2] = 0;
		mData[3] = 1;
	}

	Quaternion(const Vector3& v, float w) {
		mData[0] = v.x;
		mData[1] = v.y;
		mData[2] = v.z;
		mData[3] = w;
	}

	Quaternion(const Vector4& v) {
		mData[0] = v.x;
		mData[1] = v.y;
		mData[2] = v.z;
		mData[3] = v.w;
	}

	Quaternion(float x, float y, float z, float w) {
		mData[0] = x;
		mData[1] = y;
		mData[2] = z;
		mData[3] = w;
	}

	float x() const { return mData[0]; }
	float y() const { return mData[1]; }
	float z() const { return mData[2]; }
	float w() const { return real(); }

	Vector3 complex() const {
		return Vector3(mData[0], mData[1], mData[2]); 
	}

	void complex(const Vector3& c) {
		mData[0] = c[0]; mData[1] = c[1];  mData[2] = c[2];
	}

	float real() const {
		return mData[3];
	}

	void real(float r) {
		mData[3] = r;
	}

	Quaternion conjugate(void) const {
		return Quaternion(-complex(), real());
	}

	/**
	 * @brief Computes the inverse of this quaternion.
	 *
	 * @note This is a general inverse.  If you know a priori
	 * that you're using a unit quaternion (i.e., norm() == 1),
	 * it will be significantly faster to use conjugate() instead.
	 *
	 * @return The quaternion q such that q * (*this) == (*this) * q
	 * == [ 0 0 0 1 ]<sup>T</sup>.
	 */
	Quaternion inverse(void) const {
		return conjugate() / norm();
	}


	/**
	 * @brief Computes the product of this quaternion with the
	 * quaternion 'rhs'.
	 *
	 * @param rhs The right-hand-side of the product operation.
	 *
	 * @return The quaternion product (*this) x @p rhs.
	 */
	Quaternion product(const Quaternion& rhs) const {
		return Quaternion(y()*rhs.z() - z()*rhs.y() + x()*rhs.w() + w()*rhs.x(),
				z()*rhs.x() - x()*rhs.z() + y()*rhs.w() + w()*rhs.y(),
				x()*rhs.y() - y()*rhs.x() + z()*rhs.w() + w()*rhs.z(),
				w()*rhs.w() - x()*rhs.x() - y()*rhs.y() - z()*rhs.z());
	}

	/**
	 * @brief Quaternion product operator.
	 *
	 * The result is a quaternion such that:
	 *
	 * result.real() = (*this).real() * rhs.real() -
	 * (*this).complex().dot(rhs.complex());
	 *
	 * and:
	 *
	 * result.complex() = rhs.complex() * (*this).real
	 * + (*this).complex() * rhs.real()
	 * - (*this).complex().cross(rhs.complex());
	 *
	 * @return The quaternion product (*this) x rhs.
	 */
	Quaternion operator*(const Quaternion& rhs) const {
		return product(rhs);
	}

	/**
	 * @brief Quaternion scalar product operator.
	 * @param s A scalar by which to multiply all components
	 * of this quaternion.
	 * @return The quaternion (*this) * s.
	 */
	Quaternion operator*(float s) const {
		return Quaternion(complex()*s, real()*s);
	}

	/**
	 * @brief Produces the sum of this quaternion and rhs.
	 */
	Quaternion operator+(const Quaternion& rhs) const {
		return Quaternion(x()+rhs.x(), y()+rhs.y(), z()+rhs.z(), w()+rhs.w());
	}

	/**
	 * @brief Produces the difference of this quaternion and rhs.
	 */
	Quaternion operator-(const Quaternion& rhs) const {
		return Quaternion(x()-rhs.x(), y()-rhs.y(), z()-rhs.z(), w()-rhs.w());
	}

	/**
	 * @brief Unary negation.
	 */
	Quaternion operator-() const {
		return Quaternion(-x(), -y(), -z(), -w());
	}

	/**
	 * @brief Quaternion scalar division operator.
	 * @param s A scalar by which to divide all components
	 * of this quaternion.
	 * @return The quaternion (*this) / s.
	 */
	Quaternion operator/(float s) const {
		if (s == 0) std::clog << "Dividing quaternion by 0." << std::endl;
		return Quaternion(complex()/s, real()/s);
	}

	/**
	 * @brief Returns a matrix representation of this
	 * quaternion.
	 *
	 * Specifically this is the matrix such that:
	 *
	 * this->matrix() * q.vector() = (*this) * q for any quaternion q.
	 *
	 * Note that this is @e NOT the rotation matrix that may be
	 * represented by a unit quaternion.
	 */
	Matrix4 matrix() const {
		float m[16] = {
				w(), -z(),  y(), x(),
				z(),  w(), -x(), y(),
				-y(),  x(),  w(), z(),
				-x(), -y(), -z(), w()
		};
		return Matrix4(m);
	}

	/**
	 * @brief Returns a matrix representation of this
	 * quaternion for right multiplication.
	 *
	 * Specifically this is the matrix such that:
	 *
	 * q.vector().transpose() * this->matrix() = (q *
	 * (*this)).vector().transpose() for any quaternion q.
	 *
	 * Note that this is @e NOT the rotation matrix that may be
	 * represented by a unit quaternion.
	 */
	Matrix4 rightMatrix() const {
		float m[16] = {
				+w(), -z(),  y(), -x(),
				+z(),  w(), -x(), -y(),
				-y(),  x(),  w(), -z(),
				+x(),  y(),  z(),  w()
		};
		return Matrix4(m);
	}

	/**
	 * @brief Returns this quaternion as a 4-vector.
	 *
	 * This is simply the vector [x y z w]<sup>T</sup>
	 */
	Vector4 vector() const {
		return Vector4(mData[0], mData[1], mData[2], mData[3]);
	}

	/**
	 * @brief Returns the norm ("magnitude") of the quaternion.
	 * @return The 2-norm of [ w(), x(), y(), z() ]<sup>T</sup>.
	 */
	float norm() const {
		return sqrt(mData[0]*mData[0]+mData[1]*mData[1]+
				mData[2]*mData[2]+mData[3]*mData[3]);
	}

	/**
	 * @brief Computes the rotation matrix represented by a unit
	 * quaternion.
	 *
	 * @note This does not check that this quaternion is normalized.
	 * It formulaically returns the matrix, which will not be a
	 * rotation if the quaternion is non-unit.
	 */
	Matrix3 rotationMatrix() const {
		float m[9] = {
				1-2*y()*y()-2*z()*z(), 2*x()*y() - 2*z()*w(), 2*x()*z() + 2*y()*w(),
				2*x()*y() + 2*z()*w(), 1-2*x()*x()-2*z()*z(), 2*y()*z() - 2*x()*w(),
				2*x()*z() - 2*y()*w(), 2*y()*z() + 2*x()*w(), 1-2*x()*x()-2*y()*y()
		};
		return Matrix3(m);
	}

	/**
	 * @brief Returns the scaled-axis representation of this
	 * quaternion rotation.
	 */
	/*
    Vector3 scaledAxis(void) const {
      float w[3];
      HeliMath::scaled_axis_from_quaternion(w, mData);
      return Vector3(w);
    } */

	/**
	 * @brief Sets quaternion to be same as rotation by scaled axis w.
	 */
	void scaledAxis(const Vector3& w) {
		float theta = w.length();
		if (theta > 0.0001) {
			float s = sin(theta / 2.0f);
			Vector3 W(w / theta * s);
			mData[0] = W[0];
			mData[1] = W[1];
			mData[2] = W[2];
			mData[3] = cos(theta / 2.0f);
		} else {
			mData[0]=mData[1]=mData[2]=0;
			mData[3]=1.0;
		}
	}

	/**
	 * @brief Returns a vector rotated by this quaternion.
	 *
	 * Functionally equivalent to:  (rotationMatrix() * v)
	 * or (q * Quaternion(0, v) * q.inverse()).
	 *
	 * @warning conjugate() is used instead of inverse() for better
	 * performance, when this quaternion must be normalized.
	 */
	Vector3 rotatedVector(const Vector3& v) const {
		return (((*this) * Quaternion(v, 0)) * conjugate()).complex();
	}

	void rotate(float angle){
		float halfAngle = 0.5f * angle;
		float sin = sinf(halfAngle);
		mData[3] = cosf(halfAngle);
		mData[0] = sin * mData[0];
		mData[1] = sin * mData[1];
		mData[2] = sin * mData[2];
	}



	/**
	 * @brief Computes the quaternion that is equivalent to a given
	 * euler angle rotation.
	 * @param euler A 3-vector in order:  roll-pitch-yaw.
	 */
	void euler(const Vector3& euler) {
		float c1 = cos(euler[2] * 0.5f);
		float c2 = cos(euler[1] * 0.5f);
		float c3 = cos(euler[0] * 0.5f);
		float s1 = sin(euler[2] * 0.5f);
		float s2 = sin(euler[1] * 0.5f);
		float s3 = sin(euler[0] * 0.5f);

		mData[0] = c1*c2*s3 - s1*s2*c3;
		mData[1] = c1*s2*c3 + s1*c2*s3;
		mData[2] = s1*c2*c3 - c1*s2*s3;
		mData[3] = c1*c2*c3 + s1*s2*s3;
	}

	/** @brief Returns an equivalent euler angle representation of
	 * this quaternion.
	 * @return Euler angles in roll-pitch-yaw order.
	 */
	Vector3 euler(void) const {
		Vector3 euler;
		const static float PI_OVER_2 = M_PI * 0.5f;
		const static float EPSILON = 1e-10f;
		float sqw, sqx, sqy, sqz;

		// quick conversion to Euler angles to give tilt to user
		sqw = mData[3]*mData[3];
		sqx = mData[0]*mData[0];
		sqy = mData[1]*mData[1];
		sqz = mData[2]*mData[2];

		euler[1] = asin(2.0f * (mData[3]*mData[1] - mData[0]*mData[2]));
		if (PI_OVER_2 - fabs(euler[1]) > EPSILON) {
			euler[2] = atan2f(2.0f * (mData[0]*mData[1] + mData[3]*mData[2]),
					sqx - sqy - sqz + sqw);
			euler[0] = atan2f(2.0f * (mData[3]*mData[0] + mData[1]*mData[2]),
					sqw - sqx - sqy + sqz);
		} else {
			// compute heading from local 'down' vector
			euler[2] = atan2f(2*mData[1]*mData[2] - 2*mData[0]*mData[3],
					2*mData[0]*mData[2] + 2*mData[1]*mData[3]);
			euler[0] = 0.0;

			// If facing down, reverse yaw
			if (euler[1] < 0)
				euler[2] = M_PI - euler[2];
		}
		return euler;
	}

	/**
	 * @brief Computes a special representation that decouples the Z
	 * rotation.
	 *
	 * The decoupled representation is two rotations, Qxy and Qz,
	 * so that Q = Qxy * Qz.
	 */
	/*
  void decoupleZ(Quaternion* Qxy, Quaternion* Qz) const {
      Vector3 ztt(0,0,1);
      Vector3 zbt = this->rotatedVector(ztt);
      Vector3 axis_xy = ztt.cross(zbt);
	  float axis_norm = axis_xy.length();

      float axis_theta = acos(HeliMath::saturate(zbt[2], -1,+1));
      if (axis_norm > 0.00001) {
        axis_xy = axis_xy * (axis_theta/axis_norm); // limit is *1
      }

      Qxy->scaledAxis(axis_xy);
	 *Qz = (Qxy->conjugate() * (*this));
  }
	 */

	/**
	 * @brief Returns the quaternion slerped between this and q1 by fraction 0 <= t <= 1.
	 */
	/*
  Quaternion slerp(const Quaternion& q1, float t) {
    return slerp(*this, q1, t);
  }

  /// Returns quaternion that is slerped by fraction 't' between q0 and q1.
  static Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t) {

    float omega = acos(HeliMath::saturate(q0.mData[0]*q1.mData[0] +
                                           q0.mData[1]*q1.mData[1] +
                                           q0.mData[2]*q1.mData[2] +
                                           q0.mData[3]*q1.mData[3], -1,1));
    if (fabs(omega) < 1e-10) {
      omega = 1e-10;
    }
    float som = sin(omega);
    float st0 = sin((1-t) * omega) / som;
    float st1 = sin(t * omega) / som;

    return Quaternion(q0.mData[0]*st0 + q1.mData[0]*st1,
                      q0.mData[1]*st0 + q1.mData[1]*st1,
                      q0.mData[2]*st0 + q1.mData[2]*st1,
                      q0.mData[3]*st0 + q1.mData[3]*st1);
  }
	 */
	/**
	 * @brief Returns pointer to the internal array.
	 *
	 * Array is in order x,y,z,w.
	 */
	float* row(unsigned i) { return mData + i; }
	// Const version of the above.
	const float* row(unsigned i) const { return mData + i; }
};

/**
 * @brief Global operator allowing left-multiply by scalar.
 */
Quaternion operator*(float s, const Quaternion& q);


#endif /* QUATERNION_H */

