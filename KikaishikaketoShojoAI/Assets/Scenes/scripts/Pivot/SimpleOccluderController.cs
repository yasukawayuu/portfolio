using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/// <summary>
/// �g���K�[�ɐڐG�����I�u�W�F�N�g���i���j�����ɂ���@�\��񋟂���B
/// �������ɂ������I�u�W�F�N�g�ɑ΂��ẮA�}�e���A���̃V�F�[�_�[�ɁuRendering Mode = Transparent �� Standard Shader�v�ȂǁAcolor �� alpha ���w��ł�����̂��A�T�C�����邱�ƁB
/// </summary>
[RequireComponent(typeof(Collider))]
public class SimpleOccluderController : MonoBehaviour
{
    /// <summary>�i���j������Ԃɂ��鎞�ɂǂꂭ�炢�� alpha �ɂ��邩�w�肷��@0�ɋ߂Â��قǓ����ɂȂ�</summary>
    [SerializeField, Range(0f, 1f)]
    public float m_transparency = 0.2f;
    /// <summary>�i���j������Ԃ���߂鎞�ɂǂꂭ�炢�� alpha �ɂ��邩�w�肷��</summary>
    [SerializeField, Range(0f, 1f)]
    public float m_opaque = 1f;

    private void OnTriggerEnter(Collider other)
    {
        if(other.tag != "ShadowWall")
        {
            Renderer r = other.gameObject.GetComponent<Renderer>();
            ChangeAlpha(r, m_transparency);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag != "ShadowWall")
        {
            Renderer r = other.gameObject.GetComponent<Renderer>();
            ChangeAlpha(r, m_opaque);
        }
    }

    /// <summary>
    /// alpha ��ύX����
    /// </summary>
    /// <param name="renderer">alpha ��ύX���� Material �������� Renderer</param>
    /// <param name="targetAlpha">alpha ��ύX�������l</param>
    void ChangeAlpha(Renderer renderer, float targetAlpha)
    {
        if (renderer)
        {
            Material m = renderer.material;
            Color c = m.color;
            c.a = targetAlpha;
            m.color = c;
        }
    }
}
