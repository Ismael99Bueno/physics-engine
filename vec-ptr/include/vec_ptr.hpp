#ifndef VEC_PTR
#define VEC_PTR

#include <vector>
#include <cstdint>

namespace utils
{
    class vec_ptr
    {
    public:
        vec_ptr() = default;
        vec_ptr(std::vector<double> *buffer, std::size_t index);

        double &operator[](const std::size_t idx);
        const double &operator[](const std::size_t idx) const;

        explicit operator bool() const;

    private:
        std::vector<double> *m_buffer = nullptr;
        std::size_t m_index;
    };

}

#endif