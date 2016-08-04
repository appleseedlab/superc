#/usr/bin/perl

# Run jinn and check that expected Jinn errors are reported.
sub test_jinn($)
{
    local($prog)=@_;
    open FILE, "java -agentlib:jinn $prog 2>&1|" or die $!;
    local(@lines) = <FILE>;
    foreach (@lines) {
        chop;
        if (/Exception in thread .+ xtc.lang.blink.agent.JNIAssertionFailure:/) {
            printf "%25s %10s: An exception was thrown.\n", $prog, "SUCCESS";
            return;
        } elsif (/The following .+ are not released/) {
            printf "%25s %10s: Leaks are reported. \n", $prog, "SUCCESS";
            return;
        }
    }
    printf "%25s %10s: No Jinn exception found.\n", $prog, "FAIL";
}

# 16 error states in Jinn
test_jinn("ExceptionState");
test_jinn("CriticalSectionState");
test_jinn("JNIEnvState");

test_jinn("EntitySpecificTyping");
test_jinn("FixedTyping");
test_jinn("Nullness");
test_jinn("AccessControl");

test_jinn("LocalRefDangling");
test_jinn("LocalRefOverflow");

test_jinn("GlobalRefDangling");
test_jinn("GlobalRefLeak");

test_jinn("WeakGlobalRefDangling");
test_jinn("WeakGlobalRefLeak");

test_jinn("VMResourceDoubleFree");
test_jinn("VMResourceLeak");

test_jinn("MonitorLeak");


