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
    [SerializeField]
    private float lengthResting;
    
    private LineRenderer _renderer;
    
    void Start()
    {
        _renderer = GetComponent<LineRenderer>();
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
    
    public Vector2 GetForce(Transform t)
    {
        float res;
        if (anchors.Count != 0)
        {
            res = hardness * ((anchors[0].transform.position - links[0].transform.position).magnitude - lengthResting);
            return (anchors[0].transform.position - links[0].transform.position) * res;
        }

        if (links[1].transform == t)
        {
            res = hardness * ((links[0].transform.position - links[1].transform.position).magnitude - lengthResting);
            return (links[0].transform.position - links[1].transform.position) * res;
        }
        res = hardness * ((links[1].transform.position - links[0].transform.position).magnitude - lengthResting);
        return (links[1].transform.position - links[0].transform.position) * res;
        
    }
}
