using UnityEngine;
using XCharts.Runtime;
using XCharts;


public class LineChartUpdater : MonoBehaviour
{
    public LineChart timeDomain;
    private int maxDataPoints = 100;
    private int dataToUpdate;
    private int startX = 0;
    private float updateInterval = 0.5f;
    private float lastUpdateTime = 0f;

    // Start is called before the first frame update
    void Start()
    {

        
        timeDomain = GetComponent<LineChart>();
        timeDomain.SetMaxCache(maxDataPoints);
        timeDomain.AnimationEnable(false);
    }

    void Update()
    {
         
        if (Time.time - lastUpdateTime >= updateInterval)
        {
            timeDomain.AddData(0, startX, dataToUpdate);
            startX++;
            lastUpdateTime = Time.time;
        }
    }

    public void AppendData(int value)
    {
        dataToUpdate = value;
    }
}
