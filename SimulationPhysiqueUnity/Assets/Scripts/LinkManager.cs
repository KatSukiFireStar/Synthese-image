using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class LinkManager : MonoBehaviour
{
    [SerializeField]
    private List<GameObject> links = new();
    [SerializeField] 
    private List<GameObject> anchors = new();
    [SerializeField] 
    private float hardness;
    
    private float lengthResting;
    private LineRenderer _renderer;
    
    void Start()
    {
        _renderer = GetComponent<LineRenderer>();
        if (anchors.Count != 0)
        {
            _renderer.SetPosition(0, anchors[0].transform.position);
            _renderer.SetPosition(1, links[0].transform.position);
            lengthResting = (anchors[0].transform.position - links[0].transform.position).magnitude;
        }
        else
        {
            _renderer.SetPosition(0, links[0].transform.position);
            _renderer.SetPosition(1, links[1].transform.position);
            lengthResting = (links[1].transform.position - links[0].transform.position).magnitude;
        }
        
    }

    void Update()
    {
        if (anchors.Count != 0)
        {
            _renderer.SetPosition(0, anchors[0].transform.position);
            _renderer.SetPosition(1, links[0].transform.position);
        }
        else
        {
            _renderer.SetPosition(0, links[0].transform.position);
            _renderer.SetPosition(1, links[1].transform.position);
        }
    }
    
    public Vector3 GetForce(Transform t)
    {
        float res;
        if (anchors.Count != 0)
        {
            res = hardness * ((anchors[0].transform.position - links[0].transform.position).magnitude - lengthResting);
            return (anchors[0].transform.position - links[0].transform.position).normalized * res;
        }

        res = hardness * ((links[1].transform.position - links[0].transform.position).magnitude - lengthResting);
        if (links[1].transform == t)
        {
            return (links[0].transform.position - links[1].transform.position).normalized * res;
        }
        return (links[1].transform.position - links[0].transform.position).normalized * res;
        
    }
}
