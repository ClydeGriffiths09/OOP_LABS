#pragma once

#include <cstdlib>
#include <initializer_list>
#include <utility>
#include "figure.h"

namespace vector {
    const int8_t DEFAULT_ALLOCATE = 10;

    class Vector {
      public:
        Vector();

        figure::Figure& operator[](size_t pos);

        const figure::Figure& operator[](size_t pos) const;

        figure::Figure& Front() const noexcept;

        figure::Figure& Back() const noexcept;

        figure::Figure** Data() const noexcept;

        bool IsEmpty() const noexcept;

        size_t Size() const noexcept;

        size_t Capacity() const noexcept;

        void Reserve(size_t new_cap);

        void Clear() noexcept;

        void Insert(size_t pos, figure::Figure* value);

        void Erase(size_t begin_pos, size_t end_pos);

        void PushBack(figure::Figure* value);

        void PopBack();

        double TotalAreas();

        void PrintCenters();

        void PrintAreas();

        ~Vector();

        void swap(Vector& other) noexcept;

    private:
        size_t size_;
        size_t capacity_;
        figure::Figure** array_;
    };
}