struct Vector2
{
    float x, y;

    Vector2()
    {
        this->x = this->y = 0;
    }

    Vector2(float _x, float _y)
    {
        this->x = _x;
        this->y = _y;
    }

    Vector2 operator+(const Vector2& o)
    {
        Vector2 result;
        result.x = o.x + this->x;
        result.y = o.y + this->y;
        return result;
    }

    Vector2 operator-(const Vector2& o)
    {
        Vector2 result;
        result.x = o.x - this->x;
        result.y = o.y - this->y;
        return result;
    }

    Vector2 operator*(const Vector2& o)
    {
        Vector2 result;
        result.x = o.x * this->x;
        result.y = o.y * this->y;
        return result;
    }

    Vector2 operator/(const Vector2& o)
    {
        Vector2 result;
        result.x = o.x / this->x;
        result.y = o.y / this->y;
        return result;
    }

    Vector2 Abs() {
        this->x = fabsf(this->x);
        this->y = fabsf(this->y);

        return *this;
    }

    float Length2D() const
    {
        return sqrt(x * x + y * y);
    }

    float Magnitude() const
    {
        return sqrtf(this->x * this->x + this->y * this->y);
    }

    Vector2 Normalize() const
    {
        Vector2 normVec;
        normVec.x = this->x / Magnitude();
        normVec.y = this->y / Magnitude();
        return normVec;
    }

    float Distance(const Vector2& o) const {
        return sqrt( pow( this->x - o.x, 2 ) + pow( this->y - o.y, 2 ) );
    }
};