#pragma once

// Helper to declare fuzzy ranges.
#define FUZZY_RANGE(NAME, A, B, C, D)                 \
    struct NAME                                       \
    {                                                 \
        static constexpr int a = (A);                 \
        static constexpr int b = (B);                 \
        static constexpr int c = (C);                 \
        static constexpr int d = (D);                 \
        static_assert(a <= b && b <= c && c <= d,     \
                      "Invalid ordering for " #NAME); \
    }

// Encoder fuzzy sets
FUZZY_RANGE(encoder_negatif_besar, -300, -300, -300, -150);
FUZZY_RANGE(encoder_negatif_kecil, -300, -150, -150, 0);
FUZZY_RANGE(encoder_zero, -50, 0, 0, 50);
FUZZY_RANGE(encoder_positif_kecil, 0, 150, 150, 300);
FUZZY_RANGE(encoder_positif_besar, 150, 300, 300, 300);

// Delta error fuzzy sets
FUZZY_RANGE(deltaerror_turun_cepat, -100, -100, -100, -50);
FUZZY_RANGE(deltaerror_turun_lambat, -100, -50, -50, 0);
FUZZY_RANGE(deltaerror_stabil, -10, 0, 0, 10);
FUZZY_RANGE(deltaerror_naik_lambat, 0, 50, 50, 100);
FUZZY_RANGE(deltaerror_naik_cepat, 50, 100, 100, 100);

// Frequency (output) fuzzy sets
FUZZY_RANGE(frequency_kurangi_banyak, -10, -10, -10, -5);
FUZZY_RANGE(frequency_kurangi_sedikit, -10, -5, -5, 0);
FUZZY_RANGE(frequency_tidak_berubah, -1, 0, 0, 1);
FUZZY_RANGE(frequency_tambah_sedikit, 0, 5, 5, 10);
FUZZY_RANGE(frequency_tambah_banyak, 5, 10, 10, 10);

// Undefine helper to avoid leaking macro into other translation units.
#undef FUZZY_RANGE