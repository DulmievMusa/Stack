Compilation_Flags_W = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

main.exe : main.o stack_operations.o asserts.o
		g++ $^ ${Compilation_Flags_W} -o main.exe

run: main.exe
	.\main.exe

%.o: %.cpp
	g++ ${Compilation_Flags_W} -c $< -o $@

clean:
	rm main.exe *.o

main.o: macros.h constants.h data_types.h asserts.h