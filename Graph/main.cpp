#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//Constantes (não tão constantes) e outras var que precisam ser declaradas antes

const float pi{ static_cast<float>(std::acos(-1)) };
float constG{ 1.f };
float deltaTime{ 1.f / 60.f };


//Criar uma Class chamada DynamicBody
//Usar as var dos planetas


float Modulo(const sf::Vector2f &vector)
{
	return std::sqrt(vector.x*vector.x + vector.y*vector.y);
}
float Modulo(float x, float y)
{
	return std::sqrt(x*x + y*y);
}

sf::Vector2f Normalize(const sf::Vector2f &vector)
{
	float modulo{ Modulo(vector) };

	return sf::Vector2f(vector.x / modulo, vector.y / modulo);
}
sf::Vector2f Normalize( float x,  float y)
{
	float modulo{ Modulo(x,y) };

	return sf::Vector2f(x / modulo, y / modulo);
}






class DynamicBody
{
	sf::Vector2f m_aceleracao{ 0.f,0.f };
	sf::Vector2f m_velocidade{};

	float m_massa;

public:
	DynamicBody(float massa = 1.f): m_massa{massa}
	{
		
	}

	const sf::Vector2f getAceleracao() const { return m_aceleracao; }
	sf::Vector2f getAceleracao()  { return m_aceleracao; }

	
	void setAceleracao(sf::Vector2f aceleracao)
	{
		m_aceleracao.x = aceleracao.x;
		m_aceleracao.y = aceleracao.y;
	}
	void setAceleracao(float x, float y)
	{
		m_aceleracao.x = x;
		m_aceleracao.y = y;
	}
	

	const sf::Vector2f getVelocidade() const { return m_velocidade; }
	sf::Vector2f getVelocidade()  { return m_velocidade; }

	
	void setVelocidade(sf::Vector2f velocidade)
	{
		m_velocidade.x = velocidade.x;
		m_velocidade.y = velocidade.y;
	}
	void setVelocidade(float x, float y)
	{
		m_velocidade.x = x;
		m_velocidade.y = y;
	}

	const float getMassa() const { return m_massa; }
	float getMassa()  { return m_massa; }
	void setMassa(float massa)
	{
		m_massa = massa;
	}

	void MudancaDeVelocidade()
	{
		setVelocidade(getVelocidade() + (getAceleracao() * deltaTime));
	}

	
};

class Planeta:public DynamicBody
{

public:

	sf::CircleShape *  m_planeta{};
	
	
	Planeta(sf::CircleShape &formato, float massa = 1.f) :DynamicBody{ massa }, m_planeta{ &formato }
	{
		
	}

	sf::Vector2f ForcaDaGravidade(const Planeta &planeta)
	{
		
		sf::Vector2f raio{ planeta.m_planeta->getPosition() - m_planeta->getPosition() };
		float moduloDoRaio = Modulo(raio);

		//m*M*G/(r*r)
		return (planeta.getMassa()*getMassa()*constG / (moduloDoRaio*moduloDoRaio))*Normalize(raio);

	}

	void Deslocamento()
	{
		m_planeta->setPosition(m_planeta->getPosition() + (getVelocidade() * deltaTime));
	}
	

};


//Coisas com std::Vector
void CalcularForcasEntreTodos(const std::vector <Planeta *> &planetas)
{
	sf::Vector2f moduloDaForcaDaGravidade{ 0.f,0.f };

	int indexDoP{ 0 };
	int indexDoQ{ 0 };

	//Enquanto não pensar em algo melhor, vai ser assim
	for(Planeta * i : planetas)
	{
		i->setAceleracao(0.f,0.f );
	}

	for (Planeta * p : planetas)
	{
		for (Planeta * q : planetas)
		{

			if (indexDoQ > indexDoP) //se os planetas tiverem o index, aka serem iguais, então não tem o porque calcular isso
			{			//E se eles ja foram(index menor) tbm n tem o porque (ja que funciona não importa a direção)
				moduloDaForcaDaGravidade = p->ForcaDaGravidade(*q);


				//Somar para o planeta 'q' e 'p' no final
				//Resetar depois o moduloDaForca... -> 0.f,0.f
				p->setAceleracao(p->getAceleracao() + (moduloDaForcaDaGravidade / p->getMassa()));
				q->setAceleracao( q->getAceleracao() -(moduloDaForcaDaGravidade / q->getMassa()));

				moduloDaForcaDaGravidade = sf::Vector2f(0.f, 0.f);
			}
			indexDoQ++;
		}

		indexDoP++;
		indexDoQ = 0;
	}

}


void MoverTodos(const std::vector <Planeta *> &planetas)
{
	for (Planeta * p : planetas)
	{

		p->MudancaDeVelocidade();
		p->Deslocamento();

	}
}

//window.draw(*planetA.m_planeta)
void DesenharTodos(const std::vector <Planeta *> &planetas,  sf::RenderWindow &window)
{
	for(Planeta * p : planetas)
	{
		window.draw(*p->m_planeta);
	}

}
//--

//Gerar o Hash code de strings
long long GerarHash(std::string const& s) 
{
	const int p = 53;
	const int m = 1e9 + 9;
	long long hash_value = 0;
	long long p_pow = 1;
	for (char c : s) {
		hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
	}
	return hash_value;
}

struct  ComandosDeSimulacaoEnum
{

	long long Criar = GerarHash("Criar");
	long long G = GerarHash("G");
	long long deltaTime = GerarHash("deltaTime");
	long long fps = GerarHash("deltaTime");

	long long Posicao = GerarHash("Posicao");
	long long Velocidade = GerarHash("Velocidade");


	long long Massa = GerarHash("Massa");
	long long Tamanho = GerarHash("Tamanho");
	long long Cor = GerarHash("Cor");
};

ComandosDeSimulacaoEnum ComandosDeSimulação;


int main()
{
	//Lendo os arquivos

	std::string caminhoDoArquivo{};

	std::cout << "Qual simulacao voce quer carregar? (Escreva todo o caminho do arquivo, com as barras assim : / ) : "<<'\n';

	std::getline(std::cin , caminhoDoArquivo);

	std::ifstream arquivo{ caminhoDoArquivo };
	std::string linha{};
	std::string palavra{};
	std::vector <std::string> comando{};

	size_t posicao{0};


	std::vector <Planeta *> planetas{};
	unsigned int fps{ 60 };
	sf::Vector2f origem{ 500.f,250.f };

	

	if (arquivo.is_open())
	{
		while (std::getline(arquivo, linha)) // Estrutura: [comando] [o que é] [valor] ou [comando] [valor] ou [o que é] [valor] ou tudo igual mas ... [valor 1] [valor 2]
		{
			int tamanhoDoVector{ 0 };
			
			while ((posicao = linha.find(' ')) != std::string::npos)
			{
				palavra = linha.substr(0, posicao);
				
				linha.erase(0, posicao + 1);

				comando.push_back(palavra);

				tamanhoDoVector++;
			}
			long long hashDoComando{0};

			if (tamanhoDoVector > 0)
				hashDoComando = GerarHash(comando[0]);
			
				//Comando de 2 parametros: [comando] [valor] ou [o que é] [valor] 
				//Tentar descobrir uma maneira mais eficiente de comparar os valores

			if (tamanhoDoVector == 1) 
			{

				if(hashDoComando == ComandosDeSimulação.G)
					constG = std::stof(linha);
					
				else if (hashDoComando == ComandosDeSimulação.fps)
					fps = std::stoi(linha);
				
				else if(hashDoComando == ComandosDeSimulação.deltaTime)
					deltaTime = std::stof(linha);
					
				else if (hashDoComando == ComandosDeSimulação.Criar)
				{
					int numeroDePlanetas{ std::stoi(linha) };
					while (numeroDePlanetas > 0)
					{
							
						planetas.push_back(new Planeta(*new sf::CircleShape()));
						numeroDePlanetas--;
					}
				}

			}
				//[comando] [o que é] [valor]
				
			else if (tamanhoDoVector == 2)
			{
					
				if (hashDoComando == ComandosDeSimulação.Massa) 
				{
					if (planetas.size() >= std::stoi(comando[1]))
						planetas[std::stoi(comando[1])]->setMassa(std::stof(linha));
				}
					

				if (hashDoComando == ComandosDeSimulação.Tamanho)
				{
					if (planetas.size() >= std::stoi(comando[1])) 
					{
						planetas[std::stoi(comando[1])]->m_planeta->setRadius(std::stof(linha)); 
						planetas[std::stoi(comando[1])]->m_planeta->setOrigin(std::stof(linha), std::stof(linha));
					}
				}


			}

				//[comando] [o que é] [valor 1] [valor 2]

			else if(tamanhoDoVector == 3)
			{
				if (hashDoComando == ComandosDeSimulação.Posicao)
				{
					if (planetas.size() >= std::stoi(comando[1]))
						planetas[std::stoi(comando[1])]->m_planeta->setPosition(sf::Vector2f(std::stof(comando[2]), std::stof(linha)) + origem);
				}

				if (hashDoComando == ComandosDeSimulação.Velocidade)
				{
					if (planetas.size() >= std::stoi(comando[1]))
						planetas[std::stoi(comando[1])]->setVelocidade(std::stof(comando[2]), std::stof(linha));
				}
			}

				//[comando] [o que é] [valor 1] [valor 2] [valor 3]
			else if (tamanhoDoVector == 4)
			{	
				if (hashDoComando == ComandosDeSimulação.Cor)				
				{					
					if (planetas.size() >= std::stoi(comando[1]))						
						planetas[std::stoi(comando[1])]->m_planeta->setFillColor(sf::Color(std::stoi(comando[2]), std::stoi(comando[3]),std::stoi(linha)));
										   				
				}

			}

				//[comando] [o que é] [valor 1] [valor 2] [valor 3] [valor 4]
			else if (tamanhoDoVector == 5)
			{
				if (hashDoComando == ComandosDeSimulação.Cor)
				{
					if (planetas.size() >= std::stoi(comando[1]))
						planetas[std::stoi(comando[1])]->m_planeta->setFillColor(sf::Color(std::stoi(comando[2]),std::stoi(comando[3]), std::stoi(comando[4]), std::stoi(linha)) );


				}
			}
			
			comando.clear();
		}

		arquivo.close();
	}
	else
		std::cout << "Nao consegui abrir o arquivo" << '\n';

	
	

	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(1000,500),"Orbits",sf::Style::Default, settings);

	window.setFramerateLimit(fps);

	

	sf::View view(origem, sf::Vector2f(1000.f, 500.f));

	
	

	/*DynamicBody navinha{};

	sf::VertexArray navinhaForma(sf::Quads,4);

	navinhaForma[0].position = sf::Vector2f(0.f, 0.f ) ;
	navinhaForma[0].color = sf::Color::Blue;
	navinhaForma[1].position = sf::Vector2f(100.f, 0.f) ;
	navinhaForma[1].color = sf::Color::Green;
	navinhaForma[2].position = sf::Vector2f(100.f, 100.f) ;
	navinhaForma[2].color = sf::Color::White;
	navinhaForma[3].position = sf::Vector2f(0.f, 100.f) ;
	navinhaForma[3].color = sf::Color::Red;

	

	sf::Vector2f navinhaCentro{50.f,50.f};
	sf::Vector2f navinhaPosicao{ origem };*/
	

	
	view.zoom(0.01f);
	
	window.setView(view);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		


		window.clear();
		
		CalcularForcasEntreTodos(planetas);
		
		MoverTodos(planetas);
			   		 
		DesenharTodos(planetas, window);


		/*navinha.setAceleracao(0.f, 0.f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			navinha.setAceleracao(5.f * Normalize( localPosition.x - navinhaPosicao.x, localPosition.y - navinhaPosicao.y));
			
		}
		navinha.MudancaDeVelocidade();
		navinhaPosicao = navinha.getVelocidade()*deltaTime + navinhaPosicao;*/

		//COLISÕES entre retangulos e circulos: (quadrado, circulo)

		//C:\Users\ivanr\Desktop\algoritimo bola quadrado.png (o algoritimo)








		//Ajeitar os vertex da navinha
		//Criar classe com todos esse atributos e chamar BetterQuads
		/*sf::VertexArray vertexForDrawing(sf::Quads, navinhaForma.getVertexCount());
		for (int i = 0; i<navinhaForma.getVertexCount();i++)
		{
			vertexForDrawing[i].position = (navinhaForma[i].position - navinhaCentro) + navinhaPosicao;
			vertexForDrawing[i].color = navinhaForma[i].color;
		}

		window.draw(vertexForDrawing);*/
		

		window.display();
	
	}

}