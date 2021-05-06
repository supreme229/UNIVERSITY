#!/bin/bash
> brute.txt # stworzenie lub wyczyszczenie zawartości pliku

test() {
  out=$(./bomb psol.txt <<< "$1 $2 $3 $4 $5 $6") # uruchomienie bomby z argumentem i, j
  echo $out # wypisanie wszystkiego ze stdout
}

for ((i=1; i<7;i++))
do
    for ((j=1; j<7;j++))
    do
      if [[ "$j" == "$i" ]]; then
        continue
      fi
        for ((k=1; k<7;k++))
        do
          if [[ "$k" == "$i" || "$k" == "$j" ]]; then
            continue
          fi
            for ((l=1; l<7;l++))
            do
              if [[ "$l" == "$i" || "$l" == "$j" || "$l" == "$k" ]]; then
                continue
              fi
                for ((m=1; m<7;m++))
                do
                  if [[ "$m" == "$i" || "$m" == "$j" || "$m" == "$k"|| "$m" == "$l" ]]; then
                    continue
                  fi
                    for ((n=1; n<7;n++))
                    do
                      if [[ "$n" == "$i" || "$n" == "$j" || "$n" == "$k"|| "$n" == "$l" || "$n" == "$m" ]]; then
                        continue
                      fi
                        echo "i: $i j: $j k: $k l: $l m: $m n: $n $(test $i $j $k $l $m $n)" >> brute.txt
                    done
                  done
              done
          done
    done
done
