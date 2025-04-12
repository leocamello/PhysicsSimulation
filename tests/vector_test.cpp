#include <gtest/gtest.h>
#include "PhysicsSimulation/vector.h" // Include the header for Vector3
#include <cmath> // For std::sqrt, std::abs

// Helper function for comparing floats with a tolerance
bool AreFloatsClose(float a, float b, float tolerance = 1e-5f) {
    return std::abs(a - b) < tolerance;
}

// Test fixture for Vector3 tests
class Vector3Test : public ::testing::Test {
protected:
    Vector3 v1;
    Vector3 v2;
    Vector3 zero;

    void SetUp() override {
        v1.Set(1.0f, 2.0f, 3.0f);
        v2.Set(4.0f, -5.0f, 6.0f);
        zero.Set(0.0f, 0.0f, 0.0f);
    }
};

TEST_F(Vector3Test, DefaultConstructor) {
    Vector3 v;
    // Values are undefined, just check if it compiles and runs
    SUCCEED();
}

TEST_F(Vector3Test, ValueConstructor) {
    Vector3 v(1.5f, -2.5f, 3.5f);
    EXPECT_FLOAT_EQ(v.x, 1.5f);
    EXPECT_FLOAT_EQ(v.y, -2.5f);
    EXPECT_FLOAT_EQ(v.z, 3.5f);
}

TEST_F(Vector3Test, Set) {
    Vector3 v;
    v.Set(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST_F(Vector3Test, SqrLength) {
    EXPECT_FLOAT_EQ(v1.SqrLength(), 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f); // 1 + 4 + 9 = 14
    EXPECT_FLOAT_EQ(v2.SqrLength(), 4.0f*4.0f + (-5.0f)*(-5.0f) + 6.0f*6.0f); // 16 + 25 + 36 = 77
    EXPECT_FLOAT_EQ(zero.SqrLength(), 0.0f);
}

TEST_F(Vector3Test, Length) {
    EXPECT_FLOAT_EQ(v1.Length(), std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(v2.Length(), std::sqrt(77.0f));
    EXPECT_FLOAT_EQ(zero.Length(), 0.0f);
}

TEST_F(Vector3Test, Normalize) {
    Vector3 v_norm = v1;
    float len = v_norm.Normalize();
    float expected_len = std::sqrt(14.0f);
    EXPECT_FLOAT_EQ(len, expected_len);
    ASSERT_NE(expected_len, 0.0f); // Avoid division by zero
    EXPECT_TRUE(AreFloatsClose(v_norm.x, 1.0f / expected_len));
    EXPECT_TRUE(AreFloatsClose(v_norm.y, 2.0f / expected_len));
    EXPECT_TRUE(AreFloatsClose(v_norm.z, 3.0f / expected_len));
    EXPECT_TRUE(AreFloatsClose(v_norm.Length(), 1.0f)); // Check if length is now 1

    // Test normalizing zero vector
    Vector3 z_norm = zero;
    float zero_len = z_norm.Normalize();
    EXPECT_FLOAT_EQ(zero_len, 0.0f);
    EXPECT_FLOAT_EQ(z_norm.x, 0.0f);
    EXPECT_FLOAT_EQ(z_norm.y, 0.0f);
    EXPECT_FLOAT_EQ(z_norm.z, 0.0f);
    EXPECT_FLOAT_EQ(z_norm.Length(), 0.0f);
}

TEST_F(Vector3Test, OperatorAddAssignVector) {
    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x, 1.0f + 4.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f - 5.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f + 6.0f);
}

TEST_F(Vector3Test, OperatorAddAssignScalar) {
    v1 += 10.0f;
    EXPECT_FLOAT_EQ(v1.x, 1.0f + 10.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f + 10.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f + 10.0f);
}

TEST_F(Vector3Test, OperatorSubAssignVector) {
    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x, 1.0f - 4.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f - (-5.0f));
    EXPECT_FLOAT_EQ(v1.z, 3.0f - 6.0f);
}

TEST_F(Vector3Test, OperatorSubAssignScalar) {
    v1 -= 10.0f;
    EXPECT_FLOAT_EQ(v1.x, 1.0f - 10.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f - 10.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f - 10.0f);
}

TEST_F(Vector3Test, OperatorUnaryMinus) {
    Vector3 neg_v1 = -v1;
    EXPECT_FLOAT_EQ(neg_v1.x, -1.0f);
    EXPECT_FLOAT_EQ(neg_v1.y, -2.0f);
    EXPECT_FLOAT_EQ(neg_v1.z, -3.0f);
    // Ensure original is unchanged
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f);
}

TEST_F(Vector3Test, OperatorMulAssignVector) {
    v1 *= v2; // Component-wise
    EXPECT_FLOAT_EQ(v1.x, 1.0f * 4.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f * (-5.0f));
    EXPECT_FLOAT_EQ(v1.z, 3.0f * 6.0f);
}

TEST_F(Vector3Test, OperatorMulAssignScalar) {
    v1 *= 2.5f;
    EXPECT_FLOAT_EQ(v1.x, 1.0f * 2.5f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f * 2.5f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f * 2.5f);
}

TEST_F(Vector3Test, OperatorDivAssignScalar) {
    v1 /= 2.0f;
    EXPECT_FLOAT_EQ(v1.x, 1.0f / 2.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f / 2.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f / 2.0f);
    // Consider testing division by zero if you add checks
}

TEST_F(Vector3Test, FriendDotProduct) {
    float dot = Dot(v1, v2);
    // (1*4) + (2*-5) + (3*6) = 4 - 10 + 18 = 12
    EXPECT_FLOAT_EQ(dot, 12.0f);
    EXPECT_FLOAT_EQ(Dot(v1, zero), 0.0f);
}

TEST_F(Vector3Test, FriendCrossProduct) {
    Vector3 cross = Cross(v1, v2);
    // v1 = (1, 2, 3), v2 = (4, -5, 6)
    // x = (2*6) - (3*-5) = 12 - (-15) = 27
    // y = (3*4) - (1*6) = 12 - 6 = 6  -> Note the formula in code is b.x*a.z - a.x*b.z = 4*3 - 1*6 = 6
    // z = (1*-5) - (2*4) = -5 - 8 = -13
    EXPECT_FLOAT_EQ(cross.x, 27.0f);
    EXPECT_FLOAT_EQ(cross.y, 6.0f);
    EXPECT_FLOAT_EQ(cross.z, -13.0f);

    // Test cross product with zero vector
    Vector3 cross_zero = Cross(v1, zero);
    EXPECT_FLOAT_EQ(cross_zero.x, 0.0f);
    EXPECT_FLOAT_EQ(cross_zero.y, 0.0f);
    EXPECT_FLOAT_EQ(cross_zero.z, 0.0f);

    // Test cross product of a vector with itself (should be zero vector)
    Vector3 cross_self = Cross(v1, v1);
    EXPECT_FLOAT_EQ(cross_self.x, 0.0f);
    EXPECT_FLOAT_EQ(cross_self.y, 0.0f);
    EXPECT_FLOAT_EQ(cross_self.z, 0.0f);
}

// You might also want to add tests for Vector2 if it's used significantly.
// Example:
TEST(Vector2Test, BasicOperations) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(3.0f, 4.0f);
    a += b;
    EXPECT_FLOAT_EQ(a.x, 4.0f);
    EXPECT_FLOAT_EQ(a.y, 6.0f);
    EXPECT_FLOAT_EQ(a.Length(), std::sqrt(16.0f + 36.0f));
}