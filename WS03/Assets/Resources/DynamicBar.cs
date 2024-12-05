using UnityEngine;
using UnityEngine.UI;

public class DynamicBar : MonoBehaviour
{
    public RectTransform bar;
    public float maxHeight = 300f;
    public float minHeight = 10f;
    public Image barImage;

    private void Start()
    {
        if (bar == null)
        {
            Debug.LogError("bar not detected");
        }
    }

    public void UpdateBar(float decibelValue)
    {
        float clampedValue = Mathf.Clamp(decibelValue, 30, 130); 
        float normalisedValue = (clampedValue - 30) / 100f;
        float newHeight = Mathf.Lerp(minHeight, maxHeight, normalisedValue); 
        bar.sizeDelta = new Vector2(bar.sizeDelta.x, newHeight); 

        UpdateBarColor(clampedValue); 
    }

    private void UpdateBarColor(float decibelValue)
    {
        if (barImage != null)
        {
            if (decibelValue < 40) barImage.color = Color.green;
            else if (decibelValue < 80) barImage.color = Color.yellow;
            else barImage.color = Color.red;
        }
    }
}