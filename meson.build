project('logue-boy', 'cpp',
        version : '0.0.1',
        default_options : ['warning_level=3', 'cpp_std=c++11'])

gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_dep')
gtest_main_dep = gtest.get_variable('gtest_main_dep')

thread_dep = dependency('threads') # for gtest

logue_sdk_stub_mnlgxd_dep = declare_dependency(include_directories : 'libs/logue-sdk-stub/platform/minilogue-xd/inc')

osc_test_deps = [gtest_dep, gtest_main_dep, thread_dep, logue_sdk_stub_mnlgxd_dep]

noise_test = executable('noise_test', 'osc/noise/test/noise_test.cpp',
                        dependencies : osc_test_deps,
                        include_directories : 'osc/noise/src')

pulse_test = executable('pulse_test', 'osc/pulse/test/pulse_test.cpp',
                        dependencies : osc_test_deps,
                        include_directories : 'osc/pulse/src')

pokegold_test = executable('pokegold_test', 'osc/pokegold/test/pokegold_test.cpp',
                           dependencies : osc_test_deps,
                           include_directories : 'osc/pokegold/src')

test('noise oscillator', noise_test, suite: 'osc')
test('pulse oscillator', pulse_test, suite: 'osc')
test('pokegold oscillator', pokegold_test, suite: 'osc')
