#include "number_format.h"

void format_number(unsigned long long value, char* buffer, size_t buffer_size) {
    const char* suffixes[] = {"", "K", "M", "B", "T", "Q", "Qn", "Sx", "Sp", "Oc", "No", "D", "U", "Dd", "Td", "Qd", "Qnd", "Sxd", "Spd", "Ocd", "Nod", "V"}; // do 10^63
    int suffix_index = 0;
    double short_value = (double)value;

    while (short_value >= 1000.0 && suffix_index < (sizeof(suffixes) / sizeof(suffixes[0])) - 1) {
        short_value /= 1000.0;
        suffix_index++;
    }

    if (short_value < 10.0)
        snprintf(buffer, buffer_size, "%.2f%s", short_value, suffixes[suffix_index]);
    else if (short_value < 100.0)
        snprintf(buffer, buffer_size, "%.1f%s", short_value, suffixes[suffix_index]);
    else
        snprintf(buffer, buffer_size, "%.0f%s", short_value, suffixes[suffix_index]);
}
