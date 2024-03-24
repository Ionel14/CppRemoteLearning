#include <cstddef>
#include <utility>

namespace my_unique_ptr {
    template<typename T, typename Deleter = void(*)(T*)>
    class unique_ptr {

    public:
        explicit unique_ptr(T* p = nullptr, Deleter d = [](T* p){ delete p; }) : ptr(p), deleter(d) {}

        ~unique_ptr() {
            deleter_call();
        }

        unique_ptr(unique_ptr&& u) noexcept : ptr(u.ptr), deleter(std::move(u.deleter)) {
            u.ptr = nullptr;
        }

        unique_ptr& operator=(unique_ptr&& u) noexcept {
            if (this != &u) {
                deleter_call();
                ptr = u.ptr;
                deleter = std::move(u.deleter);
                u.ptr = nullptr;
            }
            return *this;
        }

        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }

        T* release() {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }

        void reset(T* p = nullptr) {
            deleter_call();
            ptr = p;
        }

        T* get() const { return ptr; }
        Deleter get_deleter() const { return deleter; }

        T& operator[](std::size_t index) const {
            return ptr[index];
        }

    private:
        T* ptr;
        Deleter deleter;

        void deleter_call() {
            if (deleter) {
                deleter(ptr);
            } else {
                delete ptr;
            }
        }

    };
}