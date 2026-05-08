#ifndef __ASENGINE_QUATERNION_H
#define __ASENGINE_QUATERNION_H



namespace ASEngine
{
    // defintion of quaternion used for 3d rotations
    struct  Quaternion
    {
        // quaternion axies
        // real part
        float x = 0.0f;
        // vector part
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        // define operaions
        Quaternion() = default;

        constexpr Quaternion(float _x, float _y, float _z, float _w): x(_x), y(_y), z (_z), w(_w)
        {
        }

        constexpr static Quaternion IDENTITY()
        {
            return Quaternion { 1.0f, 0.0f, 0.0f, 0.0f, };
        }

        constexpr static void Scale(const Quaternion &a, float scale, Quaternion &result)
        {
            result.x = scale * a.x;
            result.y = scale * a.y;
            result.z = scale * a.z;
            result.w = scale * a.w;
        }

        friend constexpr Quaternion operator*(const Quaternion& a, float scale)
        {
            Quaternion result{};
            Scale(a, scale, result);
            return result;
        }


        constexpr static void Add(const Quaternion& a, const Quaternion& b, Quaternion& result)
        {
            result.x = a.x + b.x;
            result.y = a.y + b.y;
            result.z = a.z + b.z;
            result.w = a.w + b.w;
        }

        friend constexpr Quaternion operator+(const Quaternion& a, const Quaternion& b)
        {
            Quaternion result{};
            Add(a, b, result);
            return result;
        }

        constexpr static void Substract(const Quaternion &a, const Quaternion &b, Quaternion &result)
        {
            result.x = a.x - b.x;
            result.y = a.y - b.y;
            result.z = a.z - b.z;
            result.w = a.w - b.w;
        }

        friend constexpr Quaternion operator-(const Quaternion &a, const Quaternion &b)
        {
            Quaternion result{};
            Substract(a, b, result);
            return result;
        }


        constexpr float NormSquared() const
        {
            return (x * x) + (y * y) + (z * z) + (w * w);
        }

        float Norm() const;


        constexpr Quaternion Conjugate() const
        {
            return Quaternion{x, -y, -z, -w};
        }

        constexpr Quaternion Invert() const
        {
            return Conjugate() * (1.0f / NormSquared());
        }
    };
} // namespace ASEngine


#endif // __ASENGINE_QUATERNION_H