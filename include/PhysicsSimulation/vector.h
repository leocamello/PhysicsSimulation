/**
 * @file vector.h
 * @brief Defines 2D and 3D vector classes (Vector2, Vector3) and related operations.
 * @author W. Celes (original), L. Nascimento (updated)
 * @date 2025-04-12
 */

#ifndef PHYSICS_SIMULATION_VECTOR_H
#define PHYSICS_SIMULATION_VECTOR_H

#include <cmath>     // For std::sqrt
#include <ostream>   // For std::ostream
#include <cassert>   // For assert()

// TODO: Consider uncommenting and using this namespace
// namespace PhysicsSimulation {

// Forward declarations for vector types and friend functions
struct Vector2;
struct Vector3;
std::ostream& operator<<(std::ostream& os, const Vector2& v);
std::ostream& operator<<(std::ostream& os, const Vector3& v);
constexpr float Dot (const Vector3& a, const Vector3& b) noexcept;
constexpr Vector3 Cross (const Vector3& a, const Vector3& b) noexcept;
constexpr float Dot (const Vector2& a, const Vector2& b) noexcept;

/**
 * @brief Represents a 2D vector with float components.
 *
 * Provides basic vector operations like addition, subtraction, scaling,
 * dot product, normalization, and length calculation.
 */
struct Vector2
{
    /** @brief The x-component of the vector. */
    float x = 0.0f;
    /** @brief The y-component of the vector. */
    float y = 0.0f;

    /** @brief Default constructor, initializes to (0, 0). */
    constexpr Vector2 () noexcept = default;

    /**
     * @brief Constructs a vector with specified components.
     * @param vx The initial x-component.
     * @param vy The initial y-component.
     */
    constexpr Vector2 (float vx, float vy) noexcept
        : x(vx), y(vy)
    {
    }

    /**
     * @brief Sets the components of the vector.
     * @param vx The new x-component.
     * @param vy The new y-component.
     */
    void Set (float vx, float vy) noexcept
    {
        x = vx; y = vy;
    }

    /**
     * @brief Calculates the squared length (magnitude) of the vector.
     * @return The squared length (x*x + y*y). Useful for comparisons to avoid sqrt.
     */
    constexpr float SqrLength () const noexcept
    {
        return (x*x+y*y);
    }

    /**
     * @brief Calculates the length (magnitude) of the vector.
     * @return The length (sqrt(x*x + y*y)).
     */
    float Length () const noexcept
    {
        return std::sqrt(x*x+y*y);
    }

    /**
     * @brief Normalizes the vector (makes its length equal to 1).
     * @return The original length of the vector before normalization.
     * @note If the original length is zero, the vector remains unchanged.
     */
    float Normalize () noexcept
    {
        float l = Length();
        if (l != 0.0f)
        {
            float d = 1.0f/l;
            x *= d; y *= d;
        }
        return l;
    }

    /**
     * @brief Adds another vector to this vector.
     * @param other The vector to add.
     * @return A reference to this modified vector.
     */
    Vector2& operator+= (const Vector2& other) noexcept
    {
        x += other.x; y += other.y;
        return *this;
    }

    /**
     * @brief Adds a scalar value to both components of this vector.
     * @param scalar The scalar value to add.
     * @return A reference to this modified vector.
     */
    Vector2& operator+= (float scalar) noexcept
    {
        x += scalar; y += scalar;
        return *this;
    }

    /**
     * @brief Subtracts another vector from this vector.
     * @param other The vector to subtract.
     * @return A reference to this modified vector.
     */
    Vector2& operator-= (const Vector2& other) noexcept
    {
        x -= other.x; y -= other.y;
        return *this;
    }

    /**
     * @brief Subtracts a scalar value from both components of this vector.
     * @param scalar The scalar value to subtract.
     * @return A reference to this modified vector.
     */
    Vector2& operator-= (float scalar) noexcept
    {
        x -= scalar; y -= scalar;
        return *this;
    }

    /**
     * @brief Negates this vector.
     * @return A new vector with negated components.
     */
    constexpr Vector2 operator- () const noexcept
    {
        return Vector2(-x,-y);
    }

    /**
     * @brief Performs component-wise multiplication with another vector.
     * @param other The vector to multiply by.
     * @return A reference to this modified vector.
     * @warning This is component-wise multiplication, not the dot product.
     */
    Vector2& operator*= (const Vector2& other) noexcept
    {
        x *= other.x; y *= other.y;
        return *this;
    }

    /**
     * @brief Multiplies this vector by a scalar.
     * @param scalar The scalar value to multiply by.
     * @return A reference to this modified vector.
     */
    Vector2& operator*= (float scalar) noexcept
    {
        x *= scalar; y *= scalar;
        return *this;
    }

    /**
     * @brief Divides this vector by a scalar.
     * @param scalar The scalar value to divide by.
     * @return A reference to this modified vector.
     * @warning Asserts if scalar is zero in debug builds. Behavior is undefined otherwise.
     */
    Vector2& operator/= (float scalar) noexcept
    {
        assert(scalar != 0.0f && "Vector2 division by zero!");
        // Consider adding a check or alternative behavior for release builds if needed
        float inv_scalar = 1.0f / scalar;
        x *= inv_scalar; y *= inv_scalar;
        return *this;
    }

    /** @brief Friend declaration for dot product calculation. */
    friend constexpr float Dot (const Vector2& a, const Vector2& b) noexcept;
    /** @brief Friend declaration for stream output. */
    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};


/**
 * @brief Represents a 3D vector with float components.
 *
 * Provides basic vector operations like addition, subtraction, scaling,
 * dot product, cross product, normalization, and length calculation.
 */
struct Vector3
{
    /** @brief The x-component of the vector. */
    float x = 0.0f;
    /** @brief The y-component of the vector. */
    float y = 0.0f;
    /** @brief The z-component of the vector. */
    float z = 0.0f;

    /** @brief Default constructor, initializes to (0, 0, 0). */
    constexpr Vector3 () noexcept = default;

    /**
     * @brief Constructs a vector with specified components.
     * @param vx The initial x-component.
     * @param vy The initial y-component.
     * @param vz The initial z-component.
     */
    constexpr Vector3 (float vx, float vy, float vz) noexcept
        : x(vx), y(vy), z(vz)
    {
    }

    /**
     * @brief Sets the components of the vector.
     * @param vx The new x-component.
     * @param vy The new y-component.
     * @param vz The new z-component.
     */
    void Set (float vx, float vy, float vz) noexcept
    {
        x = vx; y = vy; z = vz;
    }

    /**
     * @brief Calculates the squared length (magnitude) of the vector.
     * @return The squared length (x*x + y*y + z*z). Useful for comparisons to avoid sqrt.
     */
    constexpr float SqrLength () const noexcept
    {
        return (x*x+y*y+z*z);
    }

    /**
     * @brief Calculates the length (magnitude) of the vector.
     * @return The length (sqrt(x*x + y*y + z*z)).
     */
    float Length () const noexcept
    {
        return std::sqrt(x*x+y*y+z*z);
    }

    /**
     * @brief Normalizes the vector (makes its length equal to 1).
     * @return The original length of the vector before normalization.
     * @note If the original length is zero, the vector remains unchanged.
     */
    float Normalize () noexcept
    {
        float l = Length();
        if (l != 0.0f)
        {
            float d = 1.0f/l;
            x *= d; y *= d; z *= d;
        }
        return l;
    }

    /**
     * @brief Adds another vector to this vector.
     * @param other The vector to add.
     * @return A reference to this modified vector.
     */
    Vector3& operator+= (const Vector3& other) noexcept
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    /**
     * @brief Adds a scalar value to all components of this vector.
     * @param scalar The scalar value to add.
     * @return A reference to this modified vector.
     */
    Vector3& operator+= (float scalar) noexcept
    {
        x += scalar; y += scalar; z += scalar;
        return *this;
    }

    /**
     * @brief Subtracts another vector from this vector.
     * @param other The vector to subtract.
     * @return A reference to this modified vector.
     */
    Vector3& operator-= (const Vector3& other) noexcept
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    /**
     * @brief Subtracts a scalar value from all components of this vector.
     * @param scalar The scalar value to subtract.
     * @return A reference to this modified vector.
     */
    Vector3& operator-= (float scalar) noexcept
    {
        x -= scalar; y -= scalar; z -= scalar;
        return *this;
    }

    /**
     * @brief Negates this vector.
     * @return A new vector with negated components.
     */
    constexpr Vector3 operator- () const noexcept
    {
        return Vector3(-x,-y,-z);
    }

    /**
     * @brief Performs component-wise multiplication with another vector.
     * @param other The vector to multiply by.
     * @return A reference to this modified vector.
     * @warning This is component-wise multiplication, not the dot or cross product.
     */
    Vector3& operator*= (const Vector3& other) noexcept
    {
        x *= other.x; y *= other.y; z *= other.z;
        return *this;
    }

    /**
     * @brief Multiplies this vector by a scalar.
     * @param scalar The scalar value to multiply by.
     * @return A reference to this modified vector.
     */
    Vector3& operator*= (float scalar) noexcept
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    /**
     * @brief Divides this vector by a scalar.
     * @param scalar The scalar value to divide by.
     * @return A reference to this modified vector.
     * @warning Asserts if scalar is zero in debug builds. Behavior is undefined otherwise.
     */
    Vector3& operator/= (float scalar) noexcept
    {
        assert(scalar != 0.0f && "Vector3 division by zero!");
        // Consider adding a check or alternative behavior for release builds if needed
        float inv_scalar = 1.0f / scalar;
        x *= inv_scalar; y *= inv_scalar; z *= inv_scalar;
        return *this;
    }

    /** @brief Friend declaration for dot product calculation. */
    friend constexpr float Dot (const Vector3& a, const Vector3& b) noexcept;
    /** @brief Friend declaration for cross product calculation. */
    friend constexpr Vector3 Cross (const Vector3& a, const Vector3& b) noexcept;
    /** @brief Friend declaration for stream output. */
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

// ============================================================================
// Implementations of friend and non-member functions
// ============================================================================

// --- Vector2 Functions ---

/**
 * @brief Calculates the dot product of two 2D vectors.
 * @relates Vector2
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product (a.x*b.x + a.y*b.y).
 */
constexpr float Dot (const Vector2& a, const Vector2& b) noexcept
{
    return a.x*b.x + a.y*b.y;
}

/**
 * @brief Inserts a 2D vector representation into an output stream.
 * @relates Vector2
 * @param os The output stream.
 * @param v The vector to output.
 * @return The output stream.
 * @note Outputs in the format "(x, y)".
 */
inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

/**
 * @brief Adds two 2D vectors.
 * @relates Vector2
 * @param lhs The left-hand side vector.
 * @param rhs The right-hand side vector.
 * @return A new vector representing the sum (lhs + rhs).
 */
inline constexpr Vector2 operator+ (const Vector2& lhs, const Vector2& rhs) noexcept
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

/**
 * @brief Subtracts one 2D vector from another.
 * @relates Vector2
 * @param lhs The left-hand side vector (minuend).
 * @param rhs The right-hand side vector (subtrahend).
 * @return A new vector representing the difference (lhs - rhs).
 */
inline constexpr Vector2 operator- (const Vector2& lhs, const Vector2& rhs) noexcept
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

/**
 * @brief Multiplies a 2D vector by a scalar.
 * @relates Vector2
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return A new vector representing the scaled vector (vec * scalar).
 */
inline constexpr Vector2 operator* (const Vector2& vec, float scalar) noexcept
{
    return Vector2(vec.x * scalar, vec.y * scalar);
}

/**
 * @brief Multiplies a scalar by a 2D vector.
 * @relates Vector2
 * @param scalar The scalar value.
 * @param vec The vector.
 * @return A new vector representing the scaled vector (scalar * vec).
 */
inline constexpr Vector2 operator* (float scalar, const Vector2& vec) noexcept
{
    // Commutativity: scalar * vec == vec * scalar
    return Vector2(vec.x * scalar, vec.y * scalar);
}

/**
 * @brief Performs component-wise multiplication of two 2D vectors.
 * @relates Vector2
 * @param lhs The left-hand side vector.
 * @param rhs The right-hand side vector.
 * @return A new vector where each component is the product of the corresponding components of lhs and rhs.
 * @warning This is component-wise multiplication (Hadamard product), not the dot product.
 */
inline constexpr Vector2 operator* (const Vector2& lhs, const Vector2& rhs) noexcept // Component-wise
{
    return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

/**
 * @brief Divides a 2D vector by a scalar.
 * @relates Vector2
 * @param vec The vector.
 * @param scalar The scalar value to divide by.
 * @return A new vector representing the divided vector (vec / scalar).
 * @warning Asserts if scalar is zero in debug builds. Behavior is undefined otherwise.
 */
inline Vector2 operator/ (const Vector2& vec, float scalar) noexcept
{
    assert(scalar != 0.0f && "Vector2 division by zero!");
    // Consider adding a check or alternative behavior for release builds if needed
    float inv_scalar = 1.0f / scalar;
    return Vector2(vec.x * inv_scalar, vec.y * inv_scalar);
}


// --- Vector3 Functions ---

/**
 * @brief Calculates the dot product of two 3D vectors.
 * @relates Vector3
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product (a.x*b.x + a.y*b.y + a.z*b.z).
 */
constexpr float Dot (const Vector3& a, const Vector3& b) noexcept
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/**
 * @brief Calculates the cross product of two 3D vectors.
 * @relates Vector3
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector representing the cross product (a x b).
 */
constexpr Vector3 Cross (const Vector3& a, const Vector3& b) noexcept
{
    return Vector3(a.y*b.z - b.y*a.z,
                   b.x*a.z - a.x*b.z, // Note the order for right-handed system
                   a.x*b.y - b.x*a.y);
}

/**
 * @brief Inserts a 3D vector representation into an output stream.
 * @relates Vector3
 * @param os The output stream.
 * @param v The vector to output.
 * @return The output stream.
 * @note Outputs in the format "(x, y, z)".
 */
inline std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

/**
 * @brief Adds two 3D vectors.
 * @relates Vector3
 * @param lhs The left-hand side vector.
 * @param rhs The right-hand side vector.
 * @return A new vector representing the sum (lhs + rhs).
 */
inline constexpr Vector3 operator+ (const Vector3& lhs, const Vector3& rhs) noexcept
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

/**
 * @brief Subtracts one 3D vector from another.
 * @relates Vector3
 * @param lhs The left-hand side vector (minuend).
 * @param rhs The right-hand side vector (subtrahend).
 * @return A new vector representing the difference (lhs - rhs).
 */
inline constexpr Vector3 operator- (const Vector3& lhs, const Vector3& rhs) noexcept
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

/**
 * @brief Multiplies a 3D vector by a scalar.
 * @relates Vector3
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return A new vector representing the scaled vector (vec * scalar).
 */
inline constexpr Vector3 operator* (const Vector3& vec, float scalar) noexcept
{
    return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

/**
 * @brief Multiplies a scalar by a 3D vector.
 * @relates Vector3
 * @param scalar The scalar value.
 * @param vec The vector.
 * @return A new vector representing the scaled vector (scalar * vec).
 */
inline constexpr Vector3 operator* (float scalar, const Vector3& vec) noexcept
{
    // Commutativity: scalar * vec == vec * scalar
    return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

/**
 * @brief Performs component-wise multiplication of two 3D vectors.
 * @relates Vector3
 * @param lhs The left-hand side vector.
 * @param rhs The right-hand side vector.
 * @return A new vector where each component is the product of the corresponding components of lhs and rhs.
 * @warning This is component-wise multiplication (Hadamard product), not the dot or cross product.
 */
inline constexpr Vector3 operator* (const Vector3& lhs, const Vector3& rhs) noexcept // Component-wise
{
    return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

/**
 * @brief Divides a 3D vector by a scalar.
 * @relates Vector3
 * @param vec The vector.
 * @param scalar The scalar value to divide by.
 * @return A new vector representing the divided vector (vec / scalar).
 * @warning Asserts if scalar is zero in debug builds. Behavior is undefined otherwise.
 */
inline Vector3 operator/ (const Vector3& vec, float scalar) noexcept
{
    assert(scalar != 0.0f && "Vector3 division by zero!");
    // Consider adding a check or alternative behavior for release builds if needed
    float inv_scalar = 1.0f / scalar;
    return Vector3(vec.x * inv_scalar, vec.y * inv_scalar, vec.z * inv_scalar);
}

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_VECTOR_H
