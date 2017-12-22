
static float u2f(unsigned u)
{
    /* Use union to preserve exact bit representation */
    union container {
        unsigned previous;
        float value;
    };
    
    union container temp;
    temp.previous = u;
    return temp.value;
}

float fpwr8(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    
    if (x < -37) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -31) {
        /* Denormalized result */
        exp = 1;
        frac = 1<<(4 * x + 37);
    } else if (x < 32) {
        /* Normalized result */
        exp = (4 * x) + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 255;
        frac = 0;
    }
    
    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}