#!/bin/bash

make

TEST_DIR="./testes"
OUTPUT_FILE="./final_output.txt"

# Limpa o arquivo de saida
> "$OUTPUT_FILE"

for test_file in "$TEST_DIR"/*; do
  if [[ -f "$test_file" ]]; then
    echo "Processing $test_file..."
    echo "$test_file" >> "$OUTPUT_FILE"
    echo "native openssl" >> "$OUTPUT_FILE"
    # openssl encrypt
    { time openssl enc -in "$test_file" -out encriptado.txt -e -aes256 -k symmetrickey; } 2>&1 | grep real >> "$OUTPUT_FILE"
    # openssl decrypt
    { time openssl enc -in encriptado.txt -out /dev/null -d -aes256 -k symmetrickey; } 2>&1 | grep real >> "$OUTPUT_FILE"
    ./main "$test_file" >> "$OUTPUT_FILE"
  fi
done

echo "All tests completed. Results written to $OUTPUT_FILE."
