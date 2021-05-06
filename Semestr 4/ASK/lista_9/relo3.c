// typedef struct {
//     long offset; /* Offset of the reference to relocate - w którym miejscu w danej sekcji musimy zrobić podmianę */
//     long type:32, /* Relocation type - typ: absolute 32-bitowy albo relatywny względem PC 32-bitowy*/
//          symbol:32; /* Symbol table index - wpis w tablicy symboli, ADDR(symbol) zwraca absolutny adres danego symbolu */
//     long addend; /* Jakaś stała (używana np. przy adresowaniu względnym żeby poprawić względny adres o 4 bajty) */
// } Elf64_Rela;

// foreach section s {
//     foreach relocation entry r {
//         long* refptr = s + r.offset; /* ptr to reference to be relocated */
//         /* Relocate a PC-relative reference */
//         if (r.type == R_X86_64_PC32) {
//             long refaddr = ADDR(s) + r.offset; /* absolutny adres miejsca w którym podmieniamy */
//             *refptr = (unsigned) (ADDR(r.symbol) - refaddr + r.addend);
//         }

//     /* Relocate an absolute reference */
//     if (r.type == R_X86_64_32)
//         *refptr = (unsigned) (ADDR(r.symbol) + r.addend);
// }

int relo3(int val)
{
  switch (val)
  {
  case 100:
    return val;
  case 101:
    return val + 1;
  case 103:
  case 104:
    return val + 3;
  case 105:
    return val + 5;
  default:
    return val + 6;
  }
}
