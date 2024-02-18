#ifndef NAGARROREMOTELEARNING_CUSTOM_UNIQUE_PTR_H
#define NAGARROREMOTELEARNING_CUSTOM_UNIQUE_PTR_H

#include <memory>

namespace custom_memory {
    template <typename T, typename Deleter = std::default_delete<T>>
    class CustomUniquePtr {
    public:
        CustomUniquePtr(T* pointer, Deleter deleter = Deleter()): pointer_(pointer), deleter_(deleter) {}

        CustomUniquePtr(const CustomUniquePtr& other) = delete;

        CustomUniquePtr& operator=(const CustomUniquePtr& other) = delete;

        CustomUniquePtr(const CustomUniquePtr&& other);

        CustomUniquePtr& operator=(const CustomUniquePtr&& other);

        ~CustomUniquePtr() {
            deleter_(pointer_);
        }

        inline T& operator*() {
            return *pointer_;
        }

        inline T* operator->() {
            return pointer_;
        }

        inline T& operator[](std::size_t i) {
            return pointer_[i];
        }

        explicit operator bool() const {
            if (pointer_ != nullptr) {
                return true;
            }

            return false;
        }

        inline T* Get() {
            return pointer_;
        }

        inline Deleter& GetDeleter() {
            return deleter_;
        }

        inline const Deleter& GetDeleter() const {
            return deleter_;
        }

        T* Release();

        void Swap(CustomUniquePtr& other);

        void Reset(T* newPointer = nullptr);

    private:
        T* pointer_;
        Deleter deleter_;
    };

    template <typename T, typename Deleter>
    CustomUniquePtr<T, Deleter>::CustomUniquePtr(const CustomUniquePtr&& other): pointer_(std::move(other.pointer_)), deleter_(std::move(other.deleter_)) {
        other.pointer_ = nullptr;
    }

    template <typename T, typename Deleter>
    CustomUniquePtr<T, Deleter>& CustomUniquePtr<T, Deleter>::operator=(const CustomUniquePtr&& other) {
        if (this != &other) {
            this->Reset(other.Release());
            deleter_ = std::move(other.deleter_);
        }

        return *this;
    }

    template <typename T, typename Deleter>
    T* CustomUniquePtr<T, Deleter>::Release() {
        T* temp = pointer_;
        pointer_ = nullptr;
        return temp;
    }

    template <typename T, typename Deleter>
    void CustomUniquePtr<T, Deleter>::Swap(CustomUniquePtr& other) {
        if (pointer_ != &other.pointer_) {
            T* temp = pointer_;
            pointer_ = other.pointer_;
            other.pointer_ = temp;
        }

        Deleter tempDeleter = deleter_;
        deleter_ = other.deleter_;
        other.deleter_ = tempDeleter;
    }

    template <typename T, typename Deleter>
    void CustomUniquePtr<T, Deleter>::Reset(T* newPointer) {
        if (pointer_ != newPointer) {
            if (pointer_ != nullptr) {
                deleter_(pointer_);
            }
            pointer_ = newPointer;
        }
    }
}

#endif
