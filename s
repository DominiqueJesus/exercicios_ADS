# 3. Escreva um programa que compare duas listas. Considere a primeira lista
# como a versão inicial e a segunda como a versão após alterações.
# Utilizando operações com conjuntos, seu programa deverá imprimir a
# lista de modificações entre essas duas versões, listando:

# a) os elementos que não mudaram
# b) os novos elementos
# c) os elementos que foram removidos

# Lista 1: livros da Bíblia do Velho Testamento
Biblia_VelhoTestamento = ['Gênesis', 'Êxodo', 'Levítico', 'Números', 'Deuteronômio', 
                        'Josué', 'Juízes', 'Rute', '1 Samuel', '2 Samuel', '1 Reis', 
                        '2 Reis', '1 Crônicas', '2 Crônicas', 'Esdras', 'Neemias', 
                        'Ester', 'Jó', 'Salmos', 'Provérbios', 'Eclesiastes', 'Cantares'
                        'Isaías', 'Jeremias', 'Lamentações', 'Ezequiel', 'Daniel',
                        'Oséias', 'Joel', 'Amós', 'Obadias', 'Jonas', 'Miquéias', 'Naum',
                        'Habacuque', 'Sofonias', 'Ageu', 'Zacarias', 'Malaquias']

# Lista 2: livros da Bíblia do Pentateuco
Biblia_LivrosProfeticos = ['Isaías', 'Jeremias', 'Lamentações', 'Ezequiel', 'Daniel',
                        'Oséias', 'Joel', 'Amós', 'Obadias', 'Jonas', 'Miquéias', 'Naum',
                        'Habacuque', 'Sofonias', 'Ageu', 'Zacarias', 'Malaquias', 'Apocalipse']

# a) os elementos que não mudaram
VelhoTestamento = set(Biblia_VelhoTestamento)
LivrosProfeticos = set(Biblia_LivrosProfeticos)

setLivrosIguais = VelhoTestamento.intersection(LivrosProfeticos)

listLivrosIguais = list(setLivrosIguais)
i = 1

print('\n- Livros Iguais (elementos que não mudaram) -\n')
for livro in listLivrosIguais:
    print(f'{i}) {livro}')
    i += 1

# b) os novos elementos
setLivrosNovos = LivrosProfeticos.difference(VelhoTestamento)

listLivrosNovos = list(setLivrosNovos)
i = 1

print('\n- Livros Adicionados (elementos novos) -\n')
for livro in listLivrosNovos:
    print(f'{i}) {livro}')
    i += 1

# c) os elementos que foram removidos

setLivrosRemovidos = VelhoTestamento.difference(LivrosProfeticos)

listLivrosRemovidos = list(setLivrosRemovidos)
i = 1

print('\n- Livros Não Incluídos (elementos removidos) -\n')
for livro in listLivrosRemovidos:
    print(f'{i}) {livro}')
    i += 1
