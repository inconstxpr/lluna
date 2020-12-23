#include <Engine/Math/Public/FloatUtils.h>

#include <stdio.h>

int main(int argc, const char* argv[])
{
        float Left = 0.1f;
        float Right = 0.2f;
        float Sum = lluna_Math_FloatUtils_Add(Left, Right);
        printf("%.2f + %.2f = %.2f\n", Left, Right, Sum);

        return 0;
}
