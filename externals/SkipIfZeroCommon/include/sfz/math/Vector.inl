namespace sfz {

// Vector struct declaration: Vector<T,N>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>::Vector(const T* arrayPtr) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		elements[i] = arrayPtr[i];
	}
}

template<typename T, size_t N>
T& Vector<T,N>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

template<typename T, size_t N>
T Vector<T,N>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

// Vector struct declaration: Vector<T,2>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,2>::Vector(const T* arrayPtr) noexcept
:
	x{arrayPtr[0]},
	y{arrayPtr[1]}
{ }

template<typename T>
Vector<T,2>::Vector(T value) noexcept
:
	x{value},
	y{value}
{ }

template<typename T>
Vector<T,2>::Vector(T x, T y) noexcept
:
	x{x},
	y{y}
{ }

template<typename T>
T& Vector<T,2>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 2);
	return elements[index];
}

template<typename T>
T Vector<T,2>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 2);
	return elements[index];
}

// Vector struct declaration: Vector<T,3>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,3>::Vector(const T* arrayPtr) noexcept
:
	x{arrayPtr[0]},
	y{arrayPtr[1]},
	z{arrayPtr[2]}
{ }

template<typename T>
Vector<T,3>::Vector(T value) noexcept
:
	x{value},
	y{value},
	z{value}
{ }

template<typename T>
Vector<T,3>::Vector(T x, T y, T z) noexcept
:
	x{x},
	y{y},
	z{z}
{ }

template<typename T>
Vector<T,3>::Vector(Vector<T,2> xy, T z) noexcept
:
	x{xy.elements[0]},
	y{xy.elements[1]},
	z{z}
{ }

template<typename T>
Vector<T,3>::Vector(T x, Vector<T,2> yz) noexcept
:
	x{x},
	y{yz.elements[0]},
	z{yz.elements[1]}
{ }

template<typename T>
T& Vector<T,3>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 3);
	return elements[index];
}

template<typename T>
T Vector<T,3>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 3);
	return elements[index];
}

// Vector struct declaration: Vector<T,4>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,4>::Vector(const T* arrayPtr) noexcept
:
	x{arrayPtr[0]},
	y{arrayPtr[1]},
	z{arrayPtr[2]},
	w{arrayPtr[3]}
{ }

template<typename T>
Vector<T,4>::Vector(T value) noexcept
:
	x{value},
	y{value},
	z{value},
	w{value}
{ }

template<typename T>
Vector<T,4>::Vector(T x, T y, T z, T w) noexcept
:
	x{x},
	y{y},
	z{z},
	w{w}
{ }

template<typename T>
Vector<T,4>::Vector(Vector<T,3> xyz, T w) noexcept
:
	x{xyz.elements[0]},
	y{xyz.elements[1]},
	z{xyz.elements[2]},
	w{w}
{ }

template<typename T>
Vector<T,4>::Vector(T x, Vector<T,3> yzw) noexcept
:
	x{x},
	y{yzw.elements[0]},
	z{yzw.elements[1]},
	w{yzw.elements[2]}
{ }

template<typename T>
Vector<T,4>::Vector(Vector<T,2> xy, Vector<T,2> zw) noexcept
:
	x{xy.elements[0]},
	y{xy.elements[1]},
	z{zw.elements[0]},
	w{zw.elements[1]}
{ }

template<typename T>
Vector<T,4>::Vector(Vector<T,2> xy, T z, T w) noexcept
:
	x{xy.elements[0]},
	y{xy.elements[1]},
	z{z},
	w{w}
{ }

template<typename T>
Vector<T,4>::Vector(T x, Vector<T,2> yz, T w) noexcept
:
	x{x},
	y{yz.elements[0]},
	z{yz.elements[1]},
	w{w}
{ }

template<typename T>
Vector<T,4>::Vector(T x, T y, Vector<T,2> zw) noexcept
:
	x{x},
	y{y},
	z{zw.elements[0]},
	w{zw.elements[1]}
{ }

template<typename T>
T& Vector<T,4>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 4);
	return elements[index];
}

template<typename T>
T Vector<T,4>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 4);
	return elements[index];
}

// Vector constants
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,3> UNIT_X() noexcept
{
	return Vector<T,3>{T(1), T(0), T(0)};
}

template<typename T>
Vector<T,3> UNIT_Y() noexcept
{
	return Vector<T,3>{T(0), T(1), T(0)};
}

template<typename T>
Vector<T,3> UNIT_Z() noexcept
{
	return Vector<T,3>{T(0), T(0), T(1)};
}

// Vector functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T length(const Vector<T,N>& vector) noexcept
{
	return T(std::sqrt(squaredLength(vector)));
}

template<typename T, size_t N>
T squaredLength(const Vector<T,N>& vector) noexcept
{
	T squaredSum = 0;
	for (size_t i = 0; i < N; ++i) {
		squaredSum += vector.elements[i]*vector.elements[i];
	}
	return squaredSum;
}

template<typename T, size_t N>
Vector<T,N> normalize(const Vector<T,N>& vector) noexcept
{
	T lengthTmp = length(vector);
	sfz_assert_debug(lengthTmp != 0);
	return vector/lengthTmp;
}

template<typename T, size_t N>
T dot(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	T product = T(0);
	for (size_t i = 0; i < N; ++i) {
		product += (left.elements[i]*right.elements[i]);
	}
	return product;
}

template<typename T>
constexpr Vector<T,3> cross(const Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	return sfz::Vector<T,3>{left.y*right.z - left.z*right.y,
	                        left.z*right.x - left.x*right.z,
	                        left.x*right.y - left.y*right.x};
}

template<typename T, size_t N>
Vector<T,N> elemMult(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> result = left;
	for (size_t i = 0; i < N; ++i) {
		result.elements[i] *= right.elements[i];
	}
	return result;
}

template<typename T, size_t N>
T sum(const Vector<T,N>& vector) noexcept
{
	T result = T(0);
	for (size_t i = 0; i < N; ++i) {
		result += vector.elements[i];
	}
	return result;
}

template<typename T, size_t N>
T angle(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	T squaredLengthLeft = squaredLength(left);
	sfz_assert_debug(squaredLengthLeft != 0);
	T squaredLengthRight = squaredLength(right);
	sfz_assert_debug(squaredLengthRight != 0);
	return std::acos(dot(left, right)/(std::sqrt(squaredLengthLeft*squaredLengthRight)));
}

template<typename T>
T angle(Vector<T,2> vector) noexcept
{
	sfz_assert_debug(!(vector.x == 0 && vector.y == 0));
	T angle = std::atan2(vector.y, vector.x);
	if (angle < T(0)) {
		angle += T(2)*PI<T>();
	}
	return angle;
}

template<typename T>
Vector<T,2> rotate(Vector<T,2> vector, T angleRadians) noexcept
{
	T cos = std::cos(angleRadians);
	T sin = std::sin(angleRadians);
	return Vector<T,2>{vector.x*cos - vector.y*sin, vector.x*sin + vector.y*cos};
}

template<typename T, size_t N>
size_t hash(const Vector<T,N>& vector) noexcept
{
	std::hash<T> hasher;
	size_t hash = 0;
	for (size_t i = 0; i < N; ++i) {
		// hash_combine algorithm from boost
		hash ^= hasher(vector.elements[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}
	return hash;
}

template<typename T, size_t N>
std::string to_string(const Vector<T,N>& vector) noexcept
{
	std::string str;
	str += "[";
	for (size_t i = 0; i < N; ++i) {
		str += std::to_string(vector.elements[i]);
		str += ", ";
	}
	str.erase(str.length()-2);
	str += "]";
	return std::move(str);
}

// Operators (arithmetic & assignment)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>& operator+= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] += right.elements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator-= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] -= right.elements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator*= (Vector<T,N>& left, T right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] *= right;
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator/= (Vector<T,N>& left, T right) noexcept
{
	sfz_assert_debug(right != T(0));
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] /= right;
	}
	return left;
}

// Operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N> operator+ (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp += right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp -= right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& vector) noexcept
{
	Vector<T,N> temp = vector;
	return (temp *= T(-1));
}

template<typename T, size_t N>
Vector<T,N> operator* (const Vector<T,N>& left, T right) noexcept
{
	Vector<T,N> temp = left;
	return (temp *= right);
}

template<typename T, size_t N>
Vector<T,N> operator* (T left, const Vector<T,N>& right) noexcept
{
	return right * left;
}

template<typename T, size_t N>
Vector<T,N> operator/ (const Vector<T,N>& left, T right) noexcept
{
	Vector<T,N> temp = left;
	return (temp /= right);
}

// Operators (comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
bool operator== (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		if (left.elements[i] != right.elements[i]) return false;
	}
	return true;
}

template<typename T, size_t N>
bool operator!= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return !(left == right);
}

// Operators (other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept
{
	return ostream << sfz::to_string(vector);
}

// Standard iterator functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T* begin(Vector<T,N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
const T* begin(const Vector<T,N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
const T* cbegin(const Vector<T,N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
T* end(Vector<T,N>& vector) noexcept
{
	return vector.elements + N;
}

template<typename T, size_t N>
const T* end(const Vector<T,N>& vector) noexcept
{
	return vector.elements + N;
}

template<typename T, size_t N>
const T* cend(const Vector<T,N>& vector) noexcept
{
	return vector.elements + N;
}

} // namespace sfz

// Specializations of standard library for sfz::Vector
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t N>
size_t hash<sfz::Vector<T,N>>::operator() (const sfz::Vector<T,N>& vector) const noexcept
{
	return sfz::hash(vector);
}

} // namespace std