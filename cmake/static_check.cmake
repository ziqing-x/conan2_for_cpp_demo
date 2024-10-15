if(ENABLE_STATIC_ANALYSIS)
  file(GLOB_RECURSE CHECK_SRCS
    ${TOP}/src/app/*.c
    ${TOP}/src/app/*.cpp
    ${TOP}/src/app/*.h
    ${TOP}/src/app/*.hpp
  )
  find_program(CPPCHECK cppcheck)

  if(CPPCHECK)
    execute_process(
      COMMAND cppcheck --std=c++11 --enable=all --quiet --force --inconclusive --language=c++ ${CHECK_SRCS}
    )
  else()
    message(FATAL_ERROR "请安装cppcheck (运行sudo apt-get install cppcheck)")
  endif()
endif()