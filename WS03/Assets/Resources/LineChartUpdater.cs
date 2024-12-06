using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;


public class LineChartUpdater : MonoBehaviour
{
    public LineChart timeDomain;
    private int maxDataPoints = 10;
    private int startX = 0;

    // Start is called before the first frame update
    void Start()
    {
        timeDomain = GetComponent<LineChart>();
        Line.AddDefaultSerie(timeDomain, "Time Domain");
        timeDomain.SetMaxCache(maxDataPoints);
    }

    public void AppendData(int value)
    {
        timeDomain.AddData(0, startX, value);
        startX++;
    }
}
