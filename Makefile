CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
SRCS = main.c variant.c lista_variant.c gestor_archivos.c aistring_w.c aistring_F.c manejador.c eleccion.c
OBJS = $(SRCS:.c=.o)
LIBS = -lssl -lcrypto -lm

TARGET = Admin

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	@echo 'Admin-->Listo para usar'

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET)
	@echo 'programa eliminado con Exito'

.PHONNY: all clean rebuild run debug
