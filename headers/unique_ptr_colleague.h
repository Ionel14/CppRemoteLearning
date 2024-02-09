#ifndef SHA_UNIQUEPOINTER_H_
#define SHA_UNIQUEPOINTER_H_

#include "Deleter.h"

#include <memory>

namespace up {

    template<typename T>
    class UniquePointer {
        public:
            UniquePointer() : ptr_(nullptr) {};
            UniquePointer(T* ptr) : ptr_(ptr) {};
            ~UniquePointer() {
                del_(ptr_);
            };

            UniquePointer(const UniquePointer&) = delete;
            UniquePointer& operator=(const UniquePointer&) = delete;

            UniquePointer(UniquePointer&& other) : ptr_(std::move(other.ptr_)), del_(std::move(other.del_)) {};

            UniquePointer& operator=(UniquePointer&& other) {
                if (this != &other) {
                    del_(ptr_);
                    ptr_ = std::move(other.ptr_);
                    del_ = std::move(other.del_);
                    other.ptr_ = nullptr;
                }
                return *this;
            };

            T* Get() {
                return ptr_;
            };

            Deleter<T> GetDeleter() {
                return del_;
            };

            T* Release() {
                T* temp = ptr_;
                ptr_ = nullptr;
                return temp;
            };

            void Reset(T* p = nullptr) {
                if (p != ptr_) {
                    del_(ptr_);
                    ptr_ = p;
                }
            }

            operator bool () {
                return (ptr_ != nullptr);
            };

            T& operator[](size_t i) {
                return *(ptr_ + i * sizeof(T));
            };

            T& operator*() {
                return *ptr_;
            };

            T* operator->() {
                return ptr_;
            };
        private:
            T* ptr_ = nullptr;
            Deleter<T> del_;
    };
} // namespace UniquePointer

#endif // SHA_UNIQUEPOINTER_H_