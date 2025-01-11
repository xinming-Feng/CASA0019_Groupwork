# **Noise Level Monitor**

**CASA0019 Group Report**

Xinming Feng

Donghao Zhang

Alp Durmusoglu

Wenhao Yang



**GitHub URL:** [https://github.com/xinming-Feng/CASA0019\_Groupwork](https://github.com/xinming-Feng/CASA0019_Groupwork).

[TOC]



---

## **1\. Introduction**

· **Answer the question “Why?”**

### **Background**

§ The current state of noise pollution and its impact on public health and quality of life.

§ Why is a real-time noise monitoring device necessary?

### **Objectives**

§ What specific problems does the project aim to solve? (e.g., real-time monitoring of environmental noise).

### **Significance**

§ Who are the target users? (e.g., city dwellers, industrial workers).

§ How does the project benefit them? (e.g., raising awareness of noise exposure).

---

## **2\. Design and Development Process**

### **2.1 Preparation and Tools**

#### **Materials and Tools**:

§ **Modeling tools**: Blender for modeling the Christmas tree and house, Bambu Studio for 3D printing.

§ **Laser cutting**: Laser-cut wood boards for the Christmas tree.

§ **3D printing**: Techniques and settings used for the house model.

§ **Programming tools**: Arduino IDE, libraries (e.g., Adafruit\_NeoPixel, WiFi, PubSubClient).

o **Setup Process**:

§ Briefly describe how the physical and digital environments were prepared.

· 

### **2.2 Hardware Device Design**

The hardware design for this project integrates various components to create a functional and interactive system for noise level detection and visualization.

#### **Hardware Components**
![prototype](/images/prototpye.jpg)
**Microcontroller (ESP8266):**  
The ESP8266 microcontroller is central to the device’s operation, handling data collection from sensors, processing, and transmitting it to external servers. Its built-in WiFi module enables seamless data upload via the MQTT protocol, allowing real-time monitoring and analysis.

**Sound Level Sensor (SEN0232):**  
A sound sensor measures noise levels by converting audio signals into measurable electrical signals represented as decibel values. This data forms the basis for visual and quantitative outputs.

**LED Strips:**  
The LED strip visually represents noise intensity using a color gradient: green for low levels, yellow for moderate, orange for high, red for very high, and magenta for extreme levels. The brightness and number of LEDs illuminated dynamically adjust based on the noise intensity.

**LCD TFT Screen:**  
The 2.4-inch LCD TFT screen displays a real-time time-domain graph of noise, offering a visual representation of sound amplitude variations. 

The picture shown below is the schematic
![schematic](/images/schematic.jpg)
**Programming Analysis**

The software implementation leverages several libraries to streamline functionality:

* **Adafruit\_NeoPixel** for controlling the LED strip.  
* **PubSubClient** for MQTT communication.  
* **WiFiClient** for network connectivity.

Key functions include:

1. Collecting sound levels from the sensor.  
2. Mapping sound intensity to LED and LCD outputs.  
3. Publishing sound data to an MQTT server for remote monitoring.  
4. Handling WiFi or MQTT connection errors to ensure system reliability.

The code’s modular design facilitates clear data flow and easy debugging. For instance, the `updateLEDColors()` function translates decibel levels into visually distinct LED patterns, while `displaySoundWave()` plots noise amplitude in real-time. Robust error handling routines guarantee consistent operation, even during network disruptions.

This hardware and software integration provides an interactive and visually engaging tool for noise monitoring and representation, with possibilities for future enhancements in usability and functionality.).

The picture below shows how the MQTT works.

![mqtt](/images/mqtt.jpg) 
### **2.3 Digital Device Design**

The digital device for the Noise Level Monitor project was developed using Unity(AR Mobile project) by creating a visually engaging and interactive dashboard and adding function into AR. 

#### **Dashboard interface design and implement**

The dashboard consists of four components, each implemented using the **XCharts** library. Below is the image and detailed information of the dashboard:
![mqtt](/images/dashboard.png) 

##### **1\. Top-Left: Topic Message and Ring Chart**

**Slogan with emoji:** There is a slogan, which was implemented using the TextMeshPro element in Unity. An emoji (`😀`) is added in the message to increase aesthetic appeal, which is implemented with **Sprite Assets**.

**The ring chart:** it directly displays the current decibel value at center with on the left.

**Maximum Decibel Reminder:** "Additional Information" section uses a TextMeshPro element to display the highest recorded decibel value during the monitoring session.

##### **2\. Top-Right: Frequency Spectrum Plot**

The plot dynamically visualizes the distribution of sound frequencies in real-time which can help analyze the acoustic composition of sound with x-axis representing frequency, and the y-axis representing amplitude.

##### **3\. Bottom-Left: Time-Domain Signal Plot**

The time-domain plot is displayed in the bottom-left section, which can show sound amplitude over time and provide a real-time waveform with x-axis representing time and the y-axis representing amplitude.

##### **4\. Bottom-Right: Decibel Bar Chart**

The bar dynamically shows the real-time decibel value with color changes. The height of the bar is adjusted to create the visual effect of a horizontal bar graph. The code is provided in the appendix.

The bar color dynamically changes based on decibel ranges:

* Green for values below 40 dB.  
* Yellow for values between 40 and 80 dB.  
* Red for values above 80 dB.

##### **5\. Central Section: Noise Exposure Gauge**

Central part is a circular gauge with a pointer, which can dynamically adjust to indicate the current decibel value.

#### **Data Transmission and Synchronization**

##### **MQTT Integration in Unity**

To ensure real-time synchronization between the physical device and the digital dashboard, the Noise Level Monitor project employs MQTT as the communication protocol. Based on the tutor in [Workshop 06](https://workshops.cetools.org/codelabs/casa0019-06-unity-ar-pd/index.html#2), the unity subscribes to the topic that physical device publishes to an MQTT broker hosted at `mqtt.cetools.org.to` receive the decibel data in real-time.

##### **Data Synchronization**

Extracted decibel data is dynamically fed into the dashboard components, such as the ring chart, bar graph, and time-domain plot. The code is provided in the appendix.

##### **Augmented Reality (AR) Integration**

The Noise Level Monitor project leverages Augmented Reality (AR) to enhance user interaction and data visualization. The dashboard can be activated by the QR Code and some functions are also added into the AR display.

**1\. QR Code Activation**

The AR module begins with scanning a QR code placed on the screen of the mobile phone. Once the QR code is scanned, the AR dashboard is projected into the real-world environment.

**2\. AR Display**

The AR module can display the digital dashboard onto the real-world scene so that users can view the real-time noise data in a 3D space. Besides, the dashboard can be manipulated using three fingers zooming in and out.

## **3\. Project Outcomes and limitation**

### **Achievements**

1. **Functional Physical Device:** The physical device can effectively collect noise and display decibel information.   
2. **Innovative Design:** The physical device is festive-themed with Christmas, which adds creativity and engagement to users.  
3. **Various Visualization:** The dashboard not only displays real-time noise data but also highlights maximum decibel values. It also changes color to enhance data comprehension  
4. **Augmented Reality Integration:**  The dashboard is integrated into an AR interface. It allows users to access in a 3D space via mobile phone, providing an immersive and interactive user experience.

### **Limitation**

1. The data presented on the dashboard is relatively limited and primarily focused on decibel levels due to limitations in the decibel sensor chosen in physical devices.  
2. The digital twin does not include a virtual representation of the physical components, reducing alignment between the two systems.  
3. The LCD screen on the physical device presents limited information.  
4. Actually, the decibel value is not accurate. Parameters need to be fine-tuned to improve the accuracy of measurements.

---

## **4\. Reflection and Future Improvements**

The Noise Level Monitor project successfully combines the physical devices, digital dashboards, and augmented reality technologies together to provide real-time noise monitoring. However, there are still some reflections for improvements and future work. 

1. **Enhance Physical device:** Fine-tune parameters of the decibel sensor is necessary to minimise the measure error, other sensors could also be considered like a microphone which can receive more information of sound. The information displayed in the LCD screen should be enriched, such as adding an encoder to show decibel value.  
2. **Expand Dashboard Content:** A reset button can be added to “additional information part” to enable measuring maximum decibel repeatedly.   
3. **Add a Decibel Alert System**: A maximum decibel threshold can be set in the dashboard to achieve an alert system. When the noise level exceeds this threshold, a pop-up alert or notification would appear to remind users.   
4. **Complete the Digital Twin:** Virtual models of the physical components such as Christmas tree can be added into the Unity AR module to act as a digital twin.

---

## **5\. Individual Contributions and Group Collaboration**  

### **Individual Contributions**

**Alp Durmusoglu** prototyped the hardware including designing circuits and writing Arduino code for controlling the LED strips and LCD screen and transmitted decibel data from the physical device to the MQTT server.

**Donghao Zhang** designed the 3D models of the Christmas tree and house using Fusion 360\. For the digital device, he developed the AR module, enabling QR code activation and interactive features such as zooming and panning.

**Xinming** **Feng** primarily focused on the digital device's backend functionality. She successfully implemented MQTT integration to synchronize real-time data from the physical device. She wrote scripts for dashboard components to ensure they dynamically responded to incoming data. Additionally, she coded the homepage website for the project. 

**Wenhao Yang** designed and implemented the entire Unity dashboard interface,developing all four charts of the dashboard using the XCharts library and adding decorative elements such as promotional messages and dynamic color schemes. 

### **Group Collaboration**

1. Wenhao Yang, Donghao Zhang and Xinming Feng collaborated together to integrate and test the whole system function well.  
2. Donghao Zhang and Xinming Feng work together to design the physical object with aesthetic purposes.  
3. Wenhao Yang collaborated with Xinming Feng to modify Unity Inspector settings and UI category for components based on her script requirements for MQTT data integration

---

## **6\. Reference**

* He, M. (2024) 'How do you get emojis to display in a Unity TextMeshPro element?', *stackoverflow*, 23 August. Available at: https://stackoverflow.com/questions/74903522/how-do-you-get-emojis-to-display-in-a-unity-textmeshpro-element (Accessed: 10 January 2025).



## **7\. Appendix**

### **1. Key code snippets**

#### **Code for formula of bar graph height:**

float clampedValue \= Mathf.Clamp(decibelValue, 30, 130);  
float normalisedValue \= (clampedValue \- 30\) / 100f;  
float newHeight \= Mathf.Lerp(minHeight, maxHeight, normalisedValue);

#### **code for subscribing and updating the dashboard:**

void Start()  
{  
    mqttClient.ConnectAsync(new MqttClientOptionsBuilder()  
        .WithTcpServer("mqtt.cetools.org", 1884)  
        .Build());  
    mqttClient.SubscribeAsync(new MqttTopicFilterBuilder()  
        .WithTopic("student/ucfnadu/sound")  
        .Build());  
    mqttClient.UseApplicationMessageReceivedHandler(e \=\>  
    {  
        string payload \= Encoding.UTF8.GetString(e.ApplicationMessage.Payload);  
        DecibelData data \= JsonUtility.FromJson\<DecibelData\>(payload);  
        UpdateDashboard(data.decibelValue);  
    });  
}  
void UpdateDashboard(float decibelValue)  
{  
    ringChart.UpdateValue(decibelValue);  
    barChart.UpdateBar(decibelValue);  
    timeDomainPlot.AddDataPoint(decibelValue);  
}

 

