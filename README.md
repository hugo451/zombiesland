# ZombieLand
<p>Projeto final da disciplina de Introdução à Programação, do curso de Engenharia de Computação da UFPB.</p>
<p>Prof.: Lincoln David Nery e Silva.</p>
<p>Alunos:</p>
<a href="https://github.com/hugo451">André Hugo</a> <br>
<a href="https://github.com/Isaac-CI">Isaac Nóbrega</a> <br>
<a href="https://github.com/lucasguedes778">Lucas Guedes</a> <br>
<a href="https://github.com/mayraamaral">Mayra Amaral</a> <br>
<a href="https://github.com/PhellipePalitot">Phellipe Palitot</a> <br>

## Documentação

<p> O jogo foi desenvolvido utilizando a biblioteca <a href="https://www.allegro.cc">Allegro 5</a>, que faz uso da linguagem C. A principal inspiração é o jogo do dinossauro do Google Chrome, que fica disponível no navegador na ausência de internet (<a href="https://tecnoblog.net/259202/origens-jogo-dinossauro-chrome/#targetText=Erro%20de%20conex%C3%A3o%2C%20que%20virou%20jogo%20(e%20procrastina%C3%A7%C3%A3o)&targetText=Tudo%20come%C3%A7ou%20com%20um%20projeto,70%2C%20chamada%20T%2DRex.">mais informações aqui</a>.) </p>

<p> O jogo é do tipo <i>endless runner</i>, em que o personagem principal é um humano, num mundo
dominado por zumbis. Os zumbis estão vindo em sua direção e para continuar vivendo, é necessário pular e continuar correndo.</p>

<p>Ao iniciar o jogo, há o menu com três opções: Iniciar, Créditos e Sair. Essas três opções são lidas como flags que iniciam partes diferentes do código. </p>

<p>Além de jogar com as teclas do teclado, é possível jogar usando um joystick via USB (essa função ainda não está totalmente otimizada, então é possível que ocorram <i>lags</i>). </p>

## Getting Started

<p>Para que seja possível jogar, é necessário instalar a IDE <a href="http://www.codeblocks.org/downloads">Code Blocks</a>. Feito isso, faça download das versões que se encontram nesse repositório e escolha com qual vai jogar. A versão 3 é a que se encontra com mais otimização e correção de <i>bugs</i>. </p>

<p>Depois de ter instalado o Code Blocks (ou se ele já estiver instalado), é hora de installar a biblioteca Allegro. Siga os passos: </p>

* Vá à parte de Files, no <a href="https://www.allegro.cc/files/">site da Allegro</a> e em Windows Binaries clique na versão mais recente do MinGW (compilador usado pelo Code Blocks). No momento em que este arquivo está sendo feito, a versão mais recente é a 4.7.0;

* Após ter baixado o arquivo .zip, descompacte e copie (Ctrl C);

* Vá até a pasta do Code Blocks nos arquivos de programas (geralmente é o caminho C:\Program Files (x86)\CodeBlocks);

* Clique sobre MinGW e cole a pasta que você copiou anteriormente;

* Renomeie a pasta colada para "allegro" sem as aspas;

* Abra o Code Blocks e clique em Settings, depois em Compiler, como mostra a imagem:

<img src="img/guide1.png" align="center">


