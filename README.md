# Sprint_SERS-PYTHON_3
#  ChargeGrid - Sprint 3

##  Integrantes
* **Carlos Affonso** - RM: 569676
* **Gabriel Oliveira Gusmão Florêncio dos Santos** - RM 573747
* **Gustavo de Souza Abreu** - RM 574080
* **Gabrieli de Lima Pettena de Oliveira** - RM 569799
* **Igor Massone Monteiro** - RM 573853
* **Temitope Kuku da Silva Ogunbanjo** - RM 573772
---

##  Sobre o Projeto
O **ChargeGrid** é um sistema de gerenciamento para estações de recarga de veículos elétricos alimentadas por energia solar. 

Nesta **Sprint 3**, desenvolvemos o protótipo funcional do controle de recarga utilizando um **Arduino Uno**. O objetivo principal é garantir que a estação só libere a energia para o veículo quando houver geração solar suficiente, otimizando o uso de fontes renováveis.

---

##  Componentes e Circuito

A simulação do protótipo foi montada no Wokwi utilizando os seguintes componentes:

* **Arduino Uno:** Processa as leituras analógicas e executa a lógica de automação.
* **Sensor LDR:** Simula a incidência de luz solar no painel fotovoltaico.
* **Potenciômetro:** Simula a medição da corrente elétrica (em Amperes) consumida durante a recarga.
* **Módulo Relé:** Atua como a chave de segurança para liberar ou cortar a passagem de energia.
* **LEDs Indicadores:**
  * **LED Verde:** Indica que há energia solar suficiente e a recarga está liberada.
  * **LED Vermelho:** Indica que a iluminação solar está baixa e a estação está em *standby*.

---

##  Funcionamento do Código

1. O Arduino lê continuamente os valores do **LDR (A0)** e do **Potenciômetro (A1)**.
2. Se a luminosidade solar captada for **maior que 20%**:
   * O Relé é acionado e o LED Verde acende.
   * A estação inicia/mantém a recarga.
3. Se a luminosidade solar for **menor ou igual a 20%**:
   * O Relé desliga e o LED Vermelho acende.
   * O fornecimento de energia é interrompido por segurança.
4. A cada 2 segundos, o sistema gera e imprime no **Serial Monitor** um pacote de telemetria formatado em **JSON**:

```json
{
  "station_id": "CHARGEGRID_UNO_01",
  "solar_pct": 85.0,
  "voltage_v": 220.0,
  "current_a": 15.5,
  "power_w": 3410.0,
  "status": "CHARGING"
}
