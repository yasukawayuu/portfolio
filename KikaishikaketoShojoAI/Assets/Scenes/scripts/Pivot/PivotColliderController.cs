using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// m_start �� m_end ���q���悤�ȃR���C�_�[�����@�\��񋟂���B
/// �l�p���_�̂悤�ȃR���C�_�[�ɂȂ邪�A���̑�����ς������ꍇ�� Box Collider �� Size.x, sixe.y ��ҏW���邱�ƁB
/// </summary>
[RequireComponent(typeof(BoxCollider))]
public class PivotColliderController : MonoBehaviour
{
    /// <summary>�R���C�_�[�̎n�_</summary>
    [SerializeField] Transform m_start;
    /// <summary>�R���C�_�[�̏I�_</summary>
    [SerializeField] Transform m_end;
    
    private Vector3 pivotPosition;
    private Vector3 dir;
    private BoxCollider col;
    private float distance;

    void Start()
    {
        col = GetComponent<BoxCollider>();

        if (!m_start || !m_end)
        {
            Debug.LogError(name + " needs both Start and End.");
        }
    }

    void Update()
    {
        if (m_start && m_end)
        {
            // �n�_�ƏI�_�̒��ԂɈړ����A�p�x�𒲐����A�R���C�_�[�̒������v�Z���Đݒ肷��
            pivotPosition = (m_end.position + m_start.position) / 2;
            transform.position = pivotPosition;
            //�n�_����I�_�����̃x�N�g�����v�Z���APivot�̐��ʂ����̕����Ɍ����Ă���
            dir = m_end.position - transform.position;
            transform.forward = dir;
            //Pivot��Size.z���n�_����I�_�̒����ɒu�������Ă���
            distance = Vector3.Distance(m_start.position, m_end.position);
            col.size = new Vector3(col.size.x, col.size.y, distance);
        }
    }
}
