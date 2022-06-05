import random
import numpy

#ЦЕЛОЧИСЛЕННОЕ КОДИРОВАНИЕ

# фитнесс функция, необходимая для оценки приспособленности особей
def fit(idividual):
    return (1/(idividual * idividual))

# Функция реализующая алгоритм рулеточной селекции
def roulette_wheel_pop(population, probabilities, number):
    chosen = []
    for n in range(number):
         r = random.random()
         prob_circle = 0
         for i in range(len(probabilities)):
             prob_circle += probabilities[i]
             if r <= prob_circle:
                 chosen.append(population[i])
                 break
    return chosen

# перевод в функции для перевода в двоичный вид и в вещетвенный особи
def to_binary(individual):
    return "{0:b}".format(individual).zfill(4)

def to_decimal(individual):
    return int(individual[:4], 2)

# перевод в функции для перевода в двоичный вид и в вещетвенный популяции
def pop_to_binary(population):
    binary_pop = []
    for individual in population:
        binary_pop.append(to_binary(individual))
    return binary_pop

def pop_to_decimal(population):
    decimal_pop = []
    for individual in population:
        decimal_pop.append(to_decimal(individual))
    return decimal_pop

# делаем особи уникальными
def get_uniq_individual(population):
    new_population = []
    for elem in population:
        if elem not in new_population:
            new_population.append(elem)
    return new_population

# функциz 1-точечного кроссинговера (создает деток<3)
def crossover(parent_1, parent_2):
    return parent_1[:4] + parent_2[4:]

# функция мутаций
def mutation(individual):
    Pm = 1/len(individual)
    result = ''
    for digit in individual:
        if (random.random() > Pm):
            result += '1' if digit == '0' else '0'
        else:
            result += digit
    return result

# функция для скрещивания всей популяции
def population_crossover(population):
    new_pop = []
    for i in range(0, len(population), 2):
        if prob > random.random():
            new_pop.append(mutation(crossover(population[i],population[i+1])))
            new_pop.append(mutation(crossover(population[i+1],population[i])))
        else:
            new_pop.append(population[i])
            new_pop.append(population[i+1])
    return new_pop

#создаем целочисленную популяцию (из рандомных значений x)
initial_population = []
for i in range(10):
    a = random.randint(0, 100)
    initial_population.append(a)
print("Целочисленная начальная популяция: ", initial_population)
print("123")

#вычисляем приспособленность начальной популяции
population_fitness = []
for i in range(len(initial_population)):
    try:
        fitness = fit(initial_population[i])
    except ZeroDivisionError:
        print('Последняя популяция № ', 1, ':', sep='')
        print(initial_population)
        for i in range(len(initial_population)):
            if initial_population[i]**2+4 == 4:
                    print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', initial_population[i]**2+4 , ' - это минимум функции', sep='')
            else:
                    print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', initial_population[i]**2+4 ,sep='')

        break
    population_fitness.append(fitness)
    print('Приспособленность особи #', i, ' равна: ', fitness, sep='')
print("")


#Вычисляем вероятность для рулеточной селекции
fitness_prob = []
for i in range(len(population_fitness)):
    prob = population_fitness[i]/sum(population_fitness)
    fitness_prob.append(prob)
    print('Вероятность скрещивания особи #', i, ' равна: ', prob, sep='')
print("")

print("Список отобранных особей: ")
print (roulette_wheel_pop(initial_population, fitness_prob, 10))

result_population = initial_population
print(result_population)
population_fitness = []

#Цикл по дальнейшей селекции и мутации
for j in range(3000):
    population_fitness = []

    for i in range(len(result_population)):
        try:
            fitness = fit(result_population[i])
        except ZeroDivisionError:
            print('Последняя популяция № ', j+3, ':', sep='')
            print(result_population)
            for i in range(len(result_population)):
                if result_population[i]**2+4 == 4:
                    print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', result_population[i]**2+4 , ' - это минимум функции', sep='')
                else:
                    print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', result_population[i]**2+4 ,sep='')
            break
        population_fitness.append(fitness)


    fitness_prob = []

    for i in range(len(population_fitness)):
        prob = population_fitness[i]/sum(population_fitness)
        fitness_prob.append(prob)

    population_for_crossover = roulette_wheel_pop(result_population,fitness_prob, 10)
    binary_population_for_crossover = pop_to_binary(population_for_crossover)
    new_population = population_crossover(binary_population_for_crossover)
    population_for_crossover = get_uniq_individual(population_for_crossover)
    new_population = pop_to_decimal(new_population)

    try:
        population_for_crossover.sort(key=fit, reverse = True)
        new_population.sort(key=fit, reverse = True)
        result_population = population_for_crossover[:2] + new_population[2:]
        print(result_population)

    except ZeroDivisionError:
        print("")
        print('Последняя популяция № ', j+3, ':', sep='')
        print(new_population)
        for i in range(len(new_population)):
            if new_population[i]**2+4 == 4:
                print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', new_population[i]**2+4 , ' - это минимум функции', sep='')
            else:
                print('Целевая функция "x^2 + 4" особи #', i, ' равна: ', new_population[i]**2+4 ,sep='')
        break

print("1")
