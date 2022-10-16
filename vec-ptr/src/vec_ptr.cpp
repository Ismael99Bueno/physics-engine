#include "vec_ptr.hpp"

namespace utils
{
    vec_ptr::vec_ptr(std::vector<double> *buffer, std::size_t index) : m_buffer(buffer), m_index(index) {}

    double &vec_ptr::operator[](const std::size_t idx) { return m_buffer->operator[](m_index + idx); }
    const double &vec_ptr::operator[](const std::size_t idx) const { return m_buffer->operator[](m_index + idx); }

    vec_ptr::operator bool() const { return m_buffer; }
}