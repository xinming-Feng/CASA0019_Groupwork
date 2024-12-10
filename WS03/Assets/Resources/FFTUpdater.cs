using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;

public class FFTUpdater : MonoBehaviour
{
    public BarChart FFT;
    private int freqBinCount = 100;
    private float[] dataBuffer;

    // Start is called before the first frame update

    void Start()
{
    FFT = GetComponent<BarChart>();
    FFT.ClearData();
    dataBuffer = new float[freqBinCount];

    for (int i = 0; i < freqBinCount; i++)
    {
        FFT.AddXAxisData($"{i}"); 
        FFT.AddData(0, 0); 
    }
}
  

    void Update()
{
    for (int i = 0; i < freqBinCount; i++)
    {
        if (float.IsNaN(dataBuffer[i]) || float.IsInfinity(dataBuffer[i]))
        {
            dataBuffer[i] = 0; 
        }
        FFT.UpdateData(0, i, dataBuffer[i]);
    }
}


    public void UpdateChart(float[] values)
{
    int binCount = freqBinCount;
    int binSize = Mathf.Max(1, values.Length / binCount); 

    for (int i = 0; i < binCount; i++)
    {
        float sum = 0f;
        int startIndex = i * binSize;
        for (int j = 0; j < binSize; j++)
        {
            if (startIndex + j < values.Length) 
            {
                sum += values[startIndex + j];
            }
        }
        float average = sum / binSize;
        dataBuffer[i] = average;
    }
}

}
