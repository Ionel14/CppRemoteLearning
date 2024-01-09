#include <cstddef>
#include <memory>
#include <utility>
#include <functional>
#include "myuniqueptr.h"

namespace smartHome{
    // Constructor
    template <typename T>
    MyUniquePtr<T>::MyUniquePtr(T* p) : ptr(p) {}
    
    // Destructor
    template <typename T>
    MyUniquePtr<T>::~MyUniquePtr() {
        delete ptr;
    }

    // Move constructor
    template <typename T>
    MyUniquePtr<T>::MyUniquePtr(MyUniquePtr&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // Move assignment operator
    template <typename T>
    MyUniquePtr<T>& MyUniquePtr<T>::operator=(MyUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Overload dereference operator
    template <typename T>
    T& MyUniquePtr<T>::operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    template <typename T>
    T* MyUniquePtr<T>::operator->() const {
        return ptr;
    }

    // Get the raw pointer
    template <typename T>
    T* MyUniquePtr<T>::get() const {
        return ptr;
    }

    // Release ownership of the pointer
    template <typename T>
    T* MyUniquePtr<T>::release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Reset the pointer
    template <typename T>
    void MyUniquePtr<T>::reset(T* p) {
        delete ptr;
        ptr = p;
    }

    // Swap pointers
    template <typename T>
    void MyUniquePtr<T>::swap(MyUniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }

    // Check if there is an associated managed object
    template <typename T>
    MyUniquePtr<T>::operator bool() const {
        return ptr != nullptr;
    }

    // Array version: provides indexed access to the managed array
    template <typename T>
    T& MyUniquePtr<T>::operator[](std::size_t index) const {
        return ptr[index];
    }
}