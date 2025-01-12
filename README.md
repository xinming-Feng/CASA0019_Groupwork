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

### **1.1 Background**

Noise pollution is a pervasive environmental issue with significant adverse effects on human health and well-being. Chronic exposure to elevated noise levels has been linked to various health problems, including cardiovascular diseases, sleep disturbances, and increased stress levels. A comprehensive review in the *European Journal of Public Health* highlights the urgent need to address environmental noise as a public health concern.([Environmental noise exposure and health outcomes: an umbrella review of systematic reviews and meta-analysis | European Journal of Public Health | Oxford Academic](https://academic.oup.com/eurpub/article/33/4/725/7111337?utm_source=chatgpt.com&login=false))

Real-time noise monitoring devices are essential tools in mitigating these health risks. They provide accurate, immediate data on noise levels, enabling timely interventions to reduce exposure. The development of embedded real-time environmental noise monitoring devices has been discussed in recent research, emphasizing their role in long-term noise monitoring and information processing.([The design of embedded environmental noise real-time monitoring device](https://www.spiedigitallibrary.org/conference-proceedings-of-spie/12744/2688879/The-design-of-embedded-environmental-noise-real-time-monitoring-device/10.1117/12.2688879.short?utm_source=chatgpt.com))

Implementing such devices can lead to better-informed public health policies and increased community awareness, ultimately improving quality of life in noise-affected areas.

### **1.2 Objectives**

The primary goal of this project is to develop a device capable of real-time monitoring and visualization of environmental noise levels. This includes accurately measuring noise intensity, presenting data in a user-friendly format, and raising awareness about noise pollution's impacts.

### **1.3 Significance**

The target users include city dwellers, and anyone exposed to potentially harmful noise levels. By offering clear, real-time data on noise levels, the project enables users to better understand their sound environment, promoting healthier living conditions and encouraging protective measures against noise exposure.

---

## **2\. Design and Development Process**

### **2.1 Preparation and Tools** · 

**Materials and Tools**:

**Modeling tools**: Blender for modeling the Christmas tree and house, Bambu Studio for 3D printing.

![img](/images/tuzhi.png)

![img](/images/xiaowu.png)

**Laser cutting**: Laser-cut wood boards for the Christmas tree.

**3D printing**: Techniques and settings used for the house model.

![img](/images/physical.jpg)

#### **Programming tools**: 

Arduino IDE, Unity,

C#,library(MathNet.Numerics.IntegralTransforms,XCharts.Runtime,TMPro),VSCode

#### **Setup Process**:

The physical device is mainly composed of an LCD display and a Christmas tree wrapped with led lights. The led lights will light up different numbers of pixels and change color with the change of decibel size, and the LCD screen will display the time domain map of real-time environmental sound.

The digital twin part built in unity hub, the ar function is added, which can be tracked and displayed according to the printed picture set on the physical device. After scanning the picture, the virtual dashboard will be displayed.

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

The dashboard consists of four components, each implemented using the [**Xcharts**](https://www.bing.com/search?q=xcharts+unity&cvid=0f956629712e480aa04bdcd274ce2a50&gs_lcrp=EgRlZGdlKgYIAxAAGEAyBggAEEUYOTIGCAEQABhAMgYIAhAAGEAyBggDEAAYQDIGCAQQABhAMgYIBRAAGEAyBggGEAAYQDIGCAcQABhAMgYICBAAGEDSAQg1ODI1ajBqMagCALACAA&FORM=ANAB01&adppc=EdgeStart&PC=HCTS) library. Below is the image and detailed information of the dashboard:

![mqtt](/images/dashboard.png )

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

**MQTT publish**:

To ensure real-time synchronization between the physical device and the digital dashboard, the Noise Level Monitor project employs MQTT as the communication protocol. Based on the tutor in [Workshop 06](https://workshops.cetools.org/codelabs/casa0019-06-unity-ar-pd/index.html#2), the unity subscribes to the topic that physical device publishes to an MQTT broker hosted at mqtt.cetools.org.to receive the decibel data in real-time.

**Data transmission：**

The information transmission of the project mainly relies on mqtt. When the amplitude information is published at mqtt.cetools.org, subscribe through mqttManager.cs. After subscribe information, amplitude information is controlled through mqttController.cs to various tables in the dashboard. The dial in this project is divided into a dynamic line chart to record the amplitude, a ring chart to record the actual decibel count, a beating "column" to assist the display of decibels and a beating bar chart to show the FFT. Since the information of the physical device published in this project is only the amplitude value, it is necessary to carry out a series of conversion of the amplitude to decibels and obtain the corresponding FFT dynamic image after Fourier transformation. The specific conversion method is as follows:

![img](/images/daima.png)

The sliding window (timeSerie) of the project is 1000 in length. After receiving the SoundLevel of publish, it will be converted into negative number form to prepare for Fourier transform (FFT). Fourier.Forward(complexes, FourierOptions.Default) performs FFT transformation to convert time domain signals into frequency domain signals. The transformed complexes array stores the amplitude and phase information of the frequency components. The complexes[i].magnitude are used to calculate the amplitude of the frequency. Finally, the data in magnitudes[i ] is used to plot the dynamics of the FFT.

![img](/images/daima2.png)

The real-time sound amplitude displayed by the dynamic line chart. Because the sound of the table needs to be displayed dynamically, a buffer should be set when the data is passed in, and the data should be deleted while the data is passed in. In this way, the dynamic balance of the overall line chart can be realized, and the overall dashboard will not be stuck due to stack overflow.

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
5. **Avoid repeat components:** There is too much repeated information in the dashboard, and the decibel value is applied to three different charts, which makes the information too messy. In future work, the charts in the dashboard can be condensed, or more information can be added.
6. **Dynamic Charts:** Because most of the built-in functions of Xchart do not support the display of dynamic charts, during dynamic data transmission, the time domain chart (dynamic line chart) will have a small section of messy code at the beginning of data input, and the messy points will disappear when the dynamic deletion is carried out after data input. At the same time, because there is no filter set in the FFT chart, a certain section of frequency signal cannot be collected in daily life, resulting in the display of dynamic bar chart is not very obvious. In future work, we might consider building in other plotting apis and using filters in the conversion and presentation of FFTS to make them more visible.

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

 

