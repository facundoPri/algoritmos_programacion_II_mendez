"""
Alumno:
Padron
Materias aprobadas
Cantidad de cuatrimestres cursados
Certificado de trabajo
Prioridad
Inscripto

Inscriptiones:
Alumnos = []
AlumnosPrioridades = {} // pone los alunmones por prioridades
turnoActual = []
Maximo de 200 turnos de inscripcion



"""

cuatrimestre_ideal = 4

'''
'''
class Alumno:
    def __init__(self, patron, materias_aprobadas, cuatrimestre_cursado, certificado_trabajo):
       self.patron = patron
       self.materias_aprobadas = materias_aprobadas
       self.cuatrimestre_cursado = cuatrimestre_cursado
       self.certificado_trabajo = certificado_trabajo
       self.prioridad = prioridad
       self.inscripto = inscripto

    def calcular_prioridad(self):
        if self.cuatrimestre_cursado < 0:
            self.cuatrimestre_cursado = 0

        calculo_prioridad = pow(self.materias_aprobadas/(self.cuatrimestres_cursado*cuatrimestre_ideal),-1)
        if self.certificado_trabajo:
            calculo_prioridad -= calculo_prioridad*0,25
        if calculo_prioridad < 1:
            calculo_prioridad = 1
        if calculo_prioridad > 100:
            calculo_prioridad = 100
        self.prioridad = int(calculo_prioridad)
        return self.prioridad

    def inscribirse(self):
        self.inscripto = True


'''
'''
class Inscripciones:
    def __init__(self, alumnos, turnos_maximos):
        self.alumnos = alumnos
        self.turnos_maximos = turnos_maximos
        self.alumnos_prioridades = {}
        self.turno_alumnos_actual = []
        self.turno_actual = 0
        self.ultima_prioridad = 0
        self.cantidad_por_turno = 0

    def agregar_alumno(self, alumno):
        self.alumno.append(alumno)
        self.cantidad_por_turno = len(self.alumnos) / self.turnos_maximos

    def calcular_prioridades(self):
        for alumno in self.alumnos:
            alumno.calcular_prioridad()
            lista_alumnos_prioridad = self.alumnos_prioridades.get(alumno.prioridad, [])
            lista_alumnos_prioridad.append(alumno)
            self.alumnos_prioridades[alumno_prioridad] = lista_alumnos_prioridad

    def generar_turno_actual(self):
        for index, alumno in enumerate(self.turno_actual):
               if alumno.inscripto:
                   self.turno_actual.pop(index)
        agregados = 0
        while agregados <= self.cantidad_por_turno or (self.turno_actual != self.turnos_maximos and len(self.turno_alumnos_actual) != 0):
            if len(self.alumnos_prioridades[self.ultima_prioridad])==0:
                self.ultima_prioridad += 1
            self.turno_alumnos_actual.append(self.alumnos_prioridades[self.ultima_prioridad].pop())
            self.turno_actual +=1

    def alumnos_en_turno(self):
        return self.turno_alumnos_acual

"""
2.
Explicacion:
La clase alumones almacena la informacion del alumno,
permite calcular la prioridad y cambiar el estado de si esta inscripto o no.
Desde esta clase se puede manejar toda la informacion individual del alumno.

La clase inscripciones almacena los alumnos totales,
almacena los alumons separados por prioridad y genera los turno.
Desde esta clase se puede clasificar los alumnos, y generar los turnos.
Los turnos se generan uno por uno, ya que el siguiente turno tambien depende
de la cantidad de alumnos que todavia no se inscribieron.

3.
Me gustaria haber utilizado un abb para almacenar los alumnos ordenandolos por prioridad,
de esta forma en vez de crear un objeto con las prioridades se podria crear un abb ordenado por
prioridad e ir sacando los primeros de este cada vez que quiera crear un turno.
El abb tambien podria ser util como remplazo del turno_actual en caso de querer implementar una funcion de busqueda
o validar si el usuario esta en el turno
"""
