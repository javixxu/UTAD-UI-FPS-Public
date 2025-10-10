# UTAD-UI-FPS-Public
 
# Sistema de Árbol de Habilidades - UTAD_UI_FPS

## Descripción General
Este proyecto implementa un sistema de árbol de habilidades interactivo desarrollado en Unreal Engine 5.5.4. El sistema permite a los jugadores desbloquear y mejorar habilidades.

## Uso del Sistema

### Para Jugadores
1. Accede al menú del árbol de habilidades pulsando la **'G'** para abrirlo y para cerrarlo
2. Selecciona las habilidades que deseas desbloquear
3. Mantén presionado el botón de actualización para procesar los cambios
4. Observa la retroalimentación para cada intento de desbloqueo

### Para Desarrolladores
1. Configura los datos de las habilidades usando Data Assets
2. Implementa la lógica de requisitos y efectos de las habilidades
3. Personaliza la interfaz visual según las necesidades del juego

## Estructura del Sistema
### Clases Principales

#### USkillTree
Widget principal que gestiona todo el sistema de árbol de habilidades.

**Responsabilidades:**
- Gestiona la colección de nodos de habilidades
- Procesa las actualizaciones del árbol
- Maneja la lógica de desbloqueo de habilidades
- Coordina la retroalimentación al usuario

**Características clave:**
- Sistema de selección múltiple de habilidades
- Validación de requisitos para desbloqueo
- Gestión de mensajes de retroalimentación

#### USkillNodeWidget
Widget que representa visualmente una habilidad individual en el árbol.

**Componentes:**
- `SkillData`: Data Asset con la información de la habilidad
- `DescriptionWidget`: Widget para mostrar detalles
- `IconImage`: Imagen representativa de la habilidad
- `Border`: Marco visual con estados de color

**Estados de color:**
- `NormalColor`: Estado base
- `HoverColor`: Al pasar el cursor
- `PressedColor`: Al ser seleccionado
- `CompletedColor`: Habilidad desbloqueada
- `DeniedColor`: No disponible

**Funcionalidades:**
- Gestión de estados visuales
- Manejo de interacciones del usuario
- Actualización automática de descripción
- Sistema de selección/deselección

#### UDescriptionSkill
Widget que muestra la información detallada de una habilidad.

**Componentes:**
- `DescriptionText`: Texto descriptivo de la habilidad
- `NameText`: Nombre de la habilidad

**Características:**
- Visibilidad controlada por hover
- Actualización dinámica de contenido
- Integración con datos de habilidad

#### USkillFeedback
Sistema de retroalimentación visual para el usuario.

**Funcionalidades:**
- Mostrar mensajes de estado
- Temporizador para mensajes
- Retroalimentación de acciones
- Gestión de múltiples mensajes

#### UHoldButtonWidget
Widget de botón que requiere mantener presionado para activar.

**Componentes:**
- `HoldButton`: Botón principal
- `HoldProgressBar`: Barra de progreso visual
- `HoldDuration`: Tiempo requerido de presión

**Características:**
- Retroalimentación visual de progreso
- Sistema de cancelación
- Evento de completado
- Estados visuales dinámicos

#### USkillSubsystem
Subsistema que gestiona la lógica del árbol de habilidades.

**Estados de Desbloqueo**:
- `CanUnlock`: La habilidad puede desbloquearse
- `AlreadyUnlocked`: Habilidad ya desbloqueada
- `NoEnoughPoints`: Puntos insuficientes
- `AlreadyMaxLevel`: Nivel máximo alcanzado
- `LevelTooLow`: Nivel del jugador insuficiente
- `InvalidSkillData`: Datos de habilidad inválidos

### Flujo de Interacción

1. **Selección de Habilidad:**
   - Usuario interactúa con USkillNodeWidget
   - Se muestra UDescriptionSkill
   - Se actualiza el estado visual

2. **Confirmación:**
   - Usuario mantiene UHoldButtonWidget
   - Se muestra progreso visual
   - Se procesa el desbloqueo

3. **Retroalimentación:**
   - USkillFeedback muestra resultado
   - Se actualizan estados visuales
   - Se reinicia el sistema para nueva selección

