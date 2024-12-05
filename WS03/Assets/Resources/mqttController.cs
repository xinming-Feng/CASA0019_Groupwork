using System;
using System.Collections.Generic;
using UnityEngine;
using MathNet.Numerics.IntegralTransforms;
using NumericsComplex = System.Numerics.Complex;

public class mqttController : MonoBehaviour
{
    [Tooltip("Optional name for the controller")]
    public string nameController = "Controller 1";
    public string tag_mqttManager = ""; //to be set on the Inspector panel. It must match one of the mqttManager.cs GameObject
    [Header("   Case Sensitive!!")]
    [Tooltip("the topic to subscribe must contain this value. !!Case Sensitive!! ")]
    public string topicSubscribed = ""; //the topic to subscribe, it need to match a topic from the mqttManager
    private float pointerValue = 0.0f;
    [Space]
    [Space]
    public GameObject objectToControl; //pointer of the gauge, or other 3D models
    [Tooltip("Select the rotation axis of the object to control")]
    public enum State { X, Y, Z };
    public State rotationAxis;
    [Space]
    [Tooltip("Direction Rotation")]
    public bool CW = true; //CW True = 1; CW False = -1
    private int rotationDirection = 1;
    [Space]
    [Space]
    [Tooltip("minimum value on the dial")]
    public float startValue = 30f; //start value of the gauge
    [Tooltip("maximum value on the dial")]
    public float endValue = 130f; // end value of the gauge
    [Tooltip("full extension of the gauge in EulerAngles")]
    public float fullAngle = 180f; // full extension of the gauge in EulerAngles

    [Tooltip("Adjust the origin of the scale. negative values CCW; positive value CW")]
    public float adjustedStart = 0f; // negative values CCW; positive value CW
    [Space]
    public mqttManager _eventSender;

    public LineChartUpdater timedomain;

   

    public List<int> timeSerie = new List<int>();

    public BarChartUpdater barChartUpdater;
    

    void Awake()
    {
        if (GameObject.FindGameObjectsWithTag(tag_mqttManager).Length > 0)
        {
            _eventSender = GameObject.FindGameObjectsWithTag(tag_mqttManager)[0].gameObject.GetComponent<mqttManager>();
            _eventSender.Connect(); //Connect tha Manager when the object is spawned
        }
        else
        {
            Debug.LogError("At least one GameObject with mqttManager component and Tag == tag_mqttManager needs to be provided");
        }
    }

    void OnEnable()
    {
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        timedomain = FindObjectOfType<LineChartUpdater>();
        barChartUpdater = FindObjectOfType<BarChartUpdater>();
    

    }

    private void OnDisable()
    {
        _eventSender.OnMessageArrived -= OnMessageArrivedHandler;
    }

    private void OnMessageArrivedHandler(mqttObj mqttObject) //the mqttObj is defined in the mqttManager.cs
    {
        //We need to check the topic of the message to know where to use it 
        if (mqttObject.topic.Contains(topicSubscribed))
        {
            var response = JsonUtility.FromJson<tasmotaSensor.Root>(mqttObject.msg);
            
            double db = 20*Math.Log10(response.soundLevel);

            pointerValue = (float) db;
            Debug.Log("Event Fired. The message, from Object " + nameController + " is = " + pointerValue);
            if (timeSerie.Count >= 10){
                timeSerie.RemoveAt(0);
            }
            timeSerie.Add(response.soundLevel);
        
            timedomain.UpdateData(timeSerie.ToArray());
            barChartUpdater.UpdateChart(db);

            NumericsComplex[] complexes = new NumericsComplex[timeSerie.Count];
            for (int i = 0; i < complexes.Length; i++){
                complexes[i] = new NumericsComplex((float)timeSerie[i],0);
            }
            Fourier.Forward(complexes,FourierOptions.Default);

            float[] magnitudes = new float[complexes.Length];
            for (int i = 0; i < complexes.Length; i++){
                magnitudes[i] = (float)complexes[i].Magnitude;
            }


           
        }
    }

    private void Update()
    {
        float step = 1.5f * Time.deltaTime;
        // ternary conditional operator https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/conditional-operator
        rotationDirection = CW ? 1 : -1;

        if (pointerValue >= startValue)
        {
            Vector3 rotationVector = new Vector3();
            //If the rotation Axis is X
            if (rotationAxis == State.X)
            {
                rotationVector = new Vector3(
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart,
                objectToControl.transform.localEulerAngles.y,
                objectToControl.transform.localEulerAngles.z);
            }
            //If the rotation Axis is Y
            else if (rotationAxis == State.Y)
            {
                rotationVector = new Vector3(
                objectToControl.transform.localEulerAngles.x,
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart,
                objectToControl.transform.localEulerAngles.z);

            }
            //If the rotation Axis is Z
            else if (rotationAxis == State.Z)
            {
                rotationVector = new Vector3(
                objectToControl.transform.localEulerAngles.x,
                objectToControl.transform.localEulerAngles.y,
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart);
            }
            objectToControl.transform.localRotation = Quaternion.Lerp(
                    objectToControl.transform.localRotation,
                    Quaternion.Euler(rotationVector),
                    step);
        }
    }
}

// Root myDeserializedClass = JsonConvert.DeserializeObject<Root>(myJsonResponse);
[Serializable]
public class tasmotaSensor
{
    [Serializable]

    public class Root
    {
        public DateTime Time;
        public int soundLevel;
    }
}