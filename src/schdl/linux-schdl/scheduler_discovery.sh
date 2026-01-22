#!/bin/bash

###################################################################
# PRÁCTICA: Exploración del Scheduler Real en Linux (Ubuntu 22.04)#
###################################################################

echo " EXPLORACIÓN DEL SCHEDULER REAL EN LINUX"


# INFORMACIÓN CONTEXTUAL

echo "## Contexto Académico"

echo "Hasta ahora hemos estudiado algoritmos teóricos de planificación:"
echo "  • FCFS (First Come First Served)"
echo "  • SJF (Shortest Job First)"
echo "  • RR (Round Robin)"

echo "En esta práctica exploramos cómo Linux implementa la planificación en un"
echo "sistema operativo real. A diferencia de los libros de texto, Linux utiliza"
echo "un scheduler moderno llamado CFS (Completely Fair Scheduler)."

# LOCALIZACIÓN DEL CÓDIGO FUENTE

echo "Paso 1 - Identificar dónde vive el kernel"

echo "El código fuente del kernel Linux se encuentra en:"
echo "  • Ubicación: /usr/src/linux-source-6.17.0/"
echo "  • Archivo comprimido: linux-source-6.17.0.tar.bz2"
echo "  • Directorio extraído: /tmp/linux-source-6.17.0/"

echo "Paso 2 - Navegar la estructura del kernel"

echo "La estructura del kernel contiene directorios para diferentes subsistemas:"
echo "  • kernel/         → Código principal del kernel"
echo "  • kernel/sched/   → Código del scheduler y planificación de procesos"
echo "  • drivers/        → Controladores de dispositivos"
echo "  • fs/             → Sistemas de archivos"
echo "  • arch/           → Código específico de arquitectura"

echo "Paso 3 - Localizar el scheduler principal"
echo "El archivo que implementa el scheduler por defecto en Linux es:"
echo "  • Ruta: kernel/sched/fair.c"
echo "  • Ubicación completa: /tmp/linux-source-6.17.0/kernel/sched/fair.c"

# ANÁLISIS DEL CÓDIGO

echo "## Código Fuente Real del Scheduler CFS"

echo "A continuación se muestra el código fuente de 'fair.c':"

# Mostrar el código fuente real del scheduler

cat /tmp/linux-source-6.17.0/kernel/sched/fair.c | head -100

# ANÁLISIS DE CONCEPTOS

echo "## Conceptos Clave del Completely Fair Scheduler (CFS)"

echo "Analizando el código anterior podemos identificar:"

echo "1. Virtual Runtime (vruntime)"
echo "   • Cada proceso tiene un 'virtual runtime' (tiempo virtual de ejecución)"
echo "   • Se calcula ponderando el tiempo real según la prioridad del proceso"
echo "   • Los procesos con menor vruntime obtienen preferencia de ejecución"
echo "   • Esto garantiza 'fairness' (equidad) entre todos los procesos"

echo "2. Red-Black Tree (Árbol Rojo-Negro)"
echo "   • El CFS usa esta estructura para organizar los procesos listos"
echo "   • Los procesos se ordenan por su vruntime"
echo "   • Permite seleccionar el siguiente proceso en O(log n)"
echo "   • Mucho más eficiente que listas simples"

echo "3. Granularidad Adaptativa"
echo "   • A diferencia de RR que usa time slices fijos, CFS es adaptativo"
echo "   • La duración del quantum depende del número de procesos en la cola"
echo "   • Se ajusta dinámicamente según la carga del sistema"
echo "   • Esto optimiza la interactividad sin sacrificar throughput"

echo "4. Referencias en el Código"
echo "   • Línea 51: #include <linux/rbtree_augmented.h>"
echo "     → Inclusión del árbol rojo-negro aumentado"
echo "   • Línea 527: static inline __maybe_unused u64 max_vruntime"
echo "     → Función para calcular tiempo virtual máximo"
echo "   • Línea 536: static inline __maybe_unused u64 min_vruntime"
echo "     → Función para calcular tiempo virtual mínimo"
echo "   • Comentarios del kernel explican la implementación de fairness"

# RELACIÓN CON ALGORITMOS TEÓRICOS

echo "Comparación con algoritmos estudiados en clase:"

echo "FCFS (First Come First Served):"
echo "  • Problema: Provoca starvation de procesos cortos"
echo "  • Problema: Un proceso largo bloquea a todos los demás"
echo "  • CFS lo soluciona: Dando a cada proceso una proporción justa de CPU"

echo "SJF (Shortest Job First):"
echo "  • Problema: Requiere conocer el tiempo de ejecución por adelantado"
echo "  • Problema: Imposible de predecir en procesos reales"
echo "  • Problema: Favorece excesivamente a procesos cortos"
echo "  • CFS lo soluciona: Siendo justo sin necesitar información del futuro"

echo "RR (Round Robin):"
echo "  • Problema: Time slice fijo causa mucho overhead si es muy pequeño"
echo "  • Problema: Si el quantum es muy grande, se pierde interactividad"
echo "  • CFS lo soluciona: Usando granularidad adaptativa, no fija"

# PREGUNTA DE REFLEXIÓN OBLIGATORIA

echo "¿Por qué Linux no implementa directamente FCFS, SJF o RR como se ven en los libros?"

echo "Linux no implementa estos algoritmos de forma literal porque fueron diseñados"
echo "para sistemas simples y no escalan bien en sistemas modernos complejos:"

echo "FCFS (First Come First Served):"
echo "  ✗ Causa starvation de procesos cortos"
echo "  ✗ Un proceso largo bloquea a todos los demás"
echo "  ✗ Falta de interactividad"
echo "  ✗ No adaptable"

echo "SJF (Shortest Job First):"
echo "  ✗ Requiere predicción imposible del tiempo de ejecución"
echo "  ✗ En Linux es imposible saber cuánto tardará un proceso"
echo "  ✗ Favorece excesivamente a procesos cortos"
echo "  ✗ Inaplicable en sistemas reales"

echo "RR (Round Robin):"
echo "  ✗ Time slice fijo no se adapta a la carga del sistema"
echo "  ✗ Si es muy pequeño: overhead excesivo de context switching"
echo "  ✗ Si es muy grande: pierde interactividad"
echo "  ✗ No escalable"

echo "VENTAJAS DEL CFS QUE IMPLEMENTA LINUX:"
echo "  ✓ Garantiza fairness matemática"
echo "  ✓ Cada proceso obtiene proporción similar de CPU"
echo "  ✓ Adaptable dinámicamente según carga"
echo "  ✓ Minimiza starvation (ningún proceso se queda sin ejecución)"
echo "  ✓ Optimiza interactividad (procesos interactivos responden rápido)"
echo "  ✓ Escalable: O(log n) para seleccionar siguiente proceso"
echo "  ✓ Soporta prioridades mediante pesos"
echo "  ✓ Load balancing inteligente entre CPUs"

# INFORMACIÓN ADICIONAL

echo "Otros archivos importantes en kernel/sched/:"

echo "  • core.c        - Núcleo del scheduler y cambio de contexto"
echo "  • fair.c        - Implementación del CFS (Completely Fair Scheduler)"
echo "  • rt.c          - Scheduler para tareas de tiempo real"
echo "  • deadline.c    - Scheduler para deadlines estrictos (EDF)"
echo "  • sched.h       - Definiciones de estructuras de datos"
echo "  • idle.c        - Manejo de CPU en idle"

echo "Conceptos avanzados del CFS:"

echo "  • Load Balancing  - Distribución inteligente entre CPUs"
echo "  • Group Scheduling - Planificación por grupos"
echo "  • PELT - Per-Entity Load Tracking"
echo "  • Deadline Scheduling - Soporte para deadlines"
echo "  • Energy Awareness - Optimización de energía"

# CONCLUSIÓN

echo "El scheduler CFS de Linux es un ejemplo paradigmático de cómo la teoría de"
echo "sistemas operativos evolucionó en la práctica para resolver problemas reales:"

echo "Los algoritmos clásicos (FCFS, SJF, RR) son excelentes herramientas educativas"
echo "para entender los conceptos fundamentales de planificación, pero en sistemas"
echo "reales necesitamos algo más sofisticado que:"

echo "  1. Garantice fairness matemática"
echo "  2. Se adapte dinámicamente a la carga"
echo "  3. Tenga buen comportamiento interactivo"
echo "  4. Escale eficientemente"
echo "  5. Sea justo incluso con procesos de diferentes características"

echo "El CFS logra todo esto usando una combinación elegante de:"
echo "  • Virtual runtime ponderado por prioridad"
echo "  • Árbol rojo-negro para O(log n) de complejidad"
echo "  • Granularidad adaptativa en lugar de quantum fijo"
echo "  • Load balancing entre CPUs"

echo "Esto demuestra que la teoría siempre debe ser validada y mejorada en la práctica."

echo "FIN DEL ANÁLISIS"
