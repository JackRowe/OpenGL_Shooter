#pragma once

template <typename T>
struct Vector2 {
	T x, y;
	
	// both empty and filled constructors
	Vector2() : x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}

#pragma region mathmatic operations
	// add
	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	// add in place
	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	// subtract
	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	// subtract in place
	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// multiply
	Vector2 operator*(T scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	// multiply in place
	Vector2& operator*=(T scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// divide
	Vector2 operator/(T scalar) const {
		return Vector2(x / scalar, y / scalar);
	}

	// divide in place
	Vector2& operator/=(T scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
#pragma endregion

#pragma region boolean operations
	// equal to
	bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	// not equal to
	bool operator!=(const Vector2& other) const {
		return x != other.x || y != other.y;
	}

	// less than
	bool operator<(const Vector2& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}

	// greater than
	bool operator>(const Vector2& other) const {
		return std::tie(x, y) > std::tie(other.x, other.y);
	}

	// less than or equal to
	bool operator<=(const Vector2& other) const {
		return std::tie(x, y) <= std::tie(other.x, other.y);
	}

	// greater than or equal to
	bool operator>=(const Vector2& other) const {
		return std::tie(x, y) >= std::tie(other.x, other.y);
	}
#pragma endregion

#pragma region functions
	T length() const {
		return std::sqrt(static_cast<T>(x * x + y * y));
	}

	Vector2 normalize const{
		T length = length();

		if (length == static_cast<T>(0)) return;

		return Vector2<T>(x / length, y / length);
	}

	T dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	T cross(const Vector2& other) const {
		return x * other.y - y * other.x;
	}
#pragma endregion
};

template <typename T>
struct Vector3 {
    T x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

#pragma region mathmatic operations

    // add
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // add in place
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // subtract
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // subtract in place
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // multiply
    Vector3 operator*(T scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // multiply in place
    Vector3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // divide
    Vector3 operator/(T scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // divide in place
    Vector3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

#pragma endregion

#pragma region boolean operations

    // equal to
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // not equal to
    bool operator!=(const Vector3& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    // less than
    bool operator<(const Vector3& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }

    // greater than
    bool operator>(const Vector3& other) const {
        return std::tie(x, y, z) > std::tie(other.x, other.y, other.z);
    }

    // less than or equal to
    bool operator<=(const Vector3& other) const {
        return std::tie(x, y, z) <= std::tie(other.x, other.y, other.z);
    }

    // greater than or equal to
    bool operator>=(const Vector3& other) const {
        return std::tie(x, y, z) >= std::tie(other.x, other.y, other.z);
    }

#pragma endregion

#pragma region functions

    T length() const {
        return std::sqrt(static_cast<T>(x * x + y * y + z * z));
    }

    Vector3 normalize() const {
        T len = length();
        if (len == static_cast<T>(0)) return *this;
        return Vector3(x / len, y / len, z / len);
    }

    T dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

#pragma endregion
};