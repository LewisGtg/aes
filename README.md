# aes

## AVISO
É NECESSÁRIO MUDAR O .h DA BIBLIOTECA OPENSSL PARA ACEITAR O NOVO PARÂMETRO QUE CONTEM A CHAVE DO ONE TIME PAD

## TODO
- [x] Trocar a Caixa-S do AES por alguma outra cifra de substituição (exceto Cifra de Cesar)
- [x] Calcular o tempo total para cifrar e decifrar arquivos de tamanhos diversos
- [x] Colocar padding para quando não houver 16 bytes lidos
- [] Calcular o custo para cifrar e decifrar de cada fase do algoritmo.
- [x] Testar e comparar os programas com diversos arquivos