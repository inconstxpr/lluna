#include <TestHelper.h>

#include <Engine/Math/Public/FloatUtils.h>

struct lluna_TestHelper_Session SessionState;

void Add_CorrectlyAdds()
{
        float Left = 0.1f;
        float Right = 0.2f;
        float Expected = Left + Right;

        float Actual = lluna_Math_FloatUtils_Add(Left, Right);

        lluna_TestHelper_CheckEqual(Actual, Expected, &SessionState, "lluna_Math_FloatUtils_Add did not return the expected value.");
}

int main(int argc, const char* argv[])
{
        lluna_TestHelper_StartSession(&SessionState, "lluna_Math_FloatUtils");

        lluna_TestHelper_RunTest(&SessionState, Add_CorrectlyAdds);

        lluna_TestHelper_FinishSession(&SessionState);
}
