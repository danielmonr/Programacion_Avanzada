/*
 * =====================================================================================
 *
 *       Filename:  concurrencia2.c
 *
 *    Description:  Considere un sistema con tres procesos fumadores y un proceso agente. Cada fumador tarda en promedio 10 segundo fumando y luego espera 20 segundos antes de fumar su siguiente cigarrillo. Además, para fumar se requiere unir los siguientes ingredientes: tabaco, papel y fósforos. Los ingredientes se obtienen de cada fumador ya que cada uno es un productor ilimitado de algún ingrediente. El agente es el encargado de colocar los ingredientes sobre una “mesa” y ponerlos disponibles para los fumadores. El agente pide a cada fumador su ingrediente correspondiente, pero si el fumador está fumando, entonces el agente se salta dicho ingrediente y va a conseguir los restantes. Si no hay ningún ingrediente disponible, el agente se va a hacer otras actividades. El proceso de solicitar un ingrediente y colocarlo sobre la mesa se realiza cada 15 segundos (cuando termina sus múltiples ocupaciones). El agente está en un proceso infinito de conseguir los ingredientes y ponerlos disponibles para los fumadores.
 *
 *        Version:  1.0
 *        Created:  07/04/16 10:02:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo (A01021514), danielmonr@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


