#ifndef MYUNIQUEPTR_H
#define MYUNIQUEPTR_H

#include <cstddef>
#include <utility>

namespace smartHome{
    template <typename T>
    class MyUniquePtr {
    private:
        T* ptr;

    public:
        // Constructor
        explicit MyUniquePtr(T* p);

        // Destructor
        ~MyUniquePtr();

        // Move constructor
        MyUniquePtr(MyUniquePtr&& other) noexcept;

        // Move assignment operator
        MyUniquePtr& operator=(MyUniquePtr&& other) noexcept;

        // Copy and copy assignment are deleted
        MyUniquePtr(const MyUniquePtr&) = delete;
        MyUniquePtr& operator=(const MyUniquePtr&) = delete;

        // Overload dereference operator
        T& operator*() const;

        // Overload arrow operator
        T* operator->() const;

        // Get the raw pointer
        T* get() const;

        // Release ownership of the pointer
        T* release();

        // Reset the pointer
        void reset(T* p = nullptr);

        // Swap pointers
        void swap(MyUniquePtr& other) noexcept;

        // Check if there is an associated managed object
        explicit operator bool() const;

        // Array version: provides indexed access to the managed array
        T& operator[](std::size_t index) const;
        
    };
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

#endif // MYUNIQUEPTR_H