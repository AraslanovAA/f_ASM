.MODEL FLAT, C
.CODE
my_assembler proc C n : dword;

       
		mov ebx, eax

		mov esi, 2

	LOOP1:
        cmp esi, ebx
		JZ LOOP_end0
		xor eax, eax

			LOOP2:
		add eax,esi
			cmp eax, ebx
			jnae LOOP2

			cmp eax, ebx
			jz LOOP_end1

			inc esi
			jmp LOOP1


		LOOP_end0:
		mov eax, 2
			ret


			LOOP_end1:
		mov eax, 1
			ret

my_assembler endp
end

