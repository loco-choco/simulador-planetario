# Simulador Planetario
Programa em que pode-se carregar simulações em 2D de corpos que geram a força gravitacional entre si

## Como Instalar

1) Clique no botão **CODE** e clique em **Dowload ZIP**, isso ira baixar todos os aquivos do repositório em um .zip

![Botão CODE com Dowaload ZIP](https://github.com/ShoosGun/simulador-planetario/blob/master/Imagens%20do%20README/CODE.jpg)

2) Com a pasta compactada baixada, abra ela e retire a pasta **Programa e alguns exemplos do uso** e coloque-a aonde desejar , é nela em que está o simulador e um exemplo de simulação; E se quiser delete o resto da pasta compactada, ela não fará diferença.


## Como Usar

1) Abra o executavel, ele abrirá uma tela de *prompt* e pedirá pelo diretório da simulação que você deseje rodar.

2) Escreva (ou cole com o botão direito do *mouse*) todo o diretório **com o nome e tipo de arquivo da simulação** no final 

(ex: C:[outros diretórios ...]/Programa e alguns exemplos do uso/3 em orbita.txt) 

3) Clique enter, se tudo ocorrer bem o programa abrirá outra tela com a simulação ocorrendo

## Como Criar Simulações

1) Crie um arquivo .txt

2) Escreva em cada linha um comando para alterar alguma propriedade, como o valor da constante Gravitacional (G), a massa de planetas, suas cores, posições, etc...

3) Teste-a no simulador

### Comandos 
(Para números com vírgula(**,**), troque-a por ponto (**.**))

#### [comando] [valor]
- Criar [número **inteiro**] -> Gera o número de planetas dado na simulação

- G [número] -> Muda o valor da constante Gravitacional (Iniciado como 1)

- fps [número **inteiro**] -> Muda quantas vezes a simulação ocorrerá em 1 segundo (Iniciado como 60); Da para usa-lo como maneira de acelerar ou desacelerar a simulação sem perder a precisão (inicial) nos dados, mas se demanda mais do computador

- deltaTime [número] -> Muda o valor usado como a variação de tempo em segundos (Iniciado como 0.01666 ou 1/60); Da para usa-lo como maneira de acelerar ou desacelerar a simulação, mas quanto maior o valor menos preciso a simulação será


(Para escolher qual planeta será editado segue-se uma ordem que vai de 0 até o valor dado para gerar os planetas menos 1)
ex:
Criar 12
1° Planeta = 0
2° Planeta = 1
...
Ultimo Planeta = 11

#### [comando] [o que é] [valor]

- Massa [Numero do Planeta] [número] -> Muda o valor da massa do planeta escolhido [em Kg] (Iniciado como 1)

- Tamanho [Numero do Planeta] [número] -> Muda o tamanho do planeta na simulação [em m] (Iniciado como 1)

#### [comando] [o que é] [valor 1] [valor 2]

- Posicao [Numero do Planeta] [número 1] [número 2] -> Muda a posição do planeta escolhido [em m] (Iniciado como 0 0)

- Velocidade [Numero do Planeta] [número 1] [número 2] -> Muda a velocidade do planeta escolhido [em m/s] (Iniciado como 0 0)

#### [comando] [o que é] [valor 1] [valor 2] [valor 3] (Opcional: [valor 4])

- Cor [Numero do Planeta] [número 1 **inteiro**] [número 2 **inteiro**] [número 3 **inteiro**] (Opcional: [número 4 **inteiro**]) -> Muda a cor do planeta escolhido seguindo a escala RGB (Iniciado como 0 0 0) (Opcional: o **número 4** muda a transparencia da cor, Iniciado como 255 [opaco] )
