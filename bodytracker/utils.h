#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Class com método e propriedades úteis a todo o sistema
 */
class Utils
{
public:
    /**
     * @brief Construtor padrão
     */
    Utils();
    ~Utils();

    /**
     * @brief Enum que representa os tipos de rotações
     */
    enum RotationEnum
    {
        ROT_X, ///< Utilizado para representar rotação no eixo X
        ROT_Y, ///< Utilizado para representar rotação no eixo Y
        ROT_Z, ///< Utilizado para representar rotação no eixo Z
        ROT_STOP ///< Utilizado para representar o fim da rotação. O objeto permanece parado.
    };

    /**
     * @brief Enum que representa os tipos de solo que podem ser desenhados
     */
    enum GroundTypeEnum
    {
        EMPTY, ///< Utilizado para representar o chão vazio.
        SQUARES, ///< Utilizado para representar o chão preenchido com quadrados.
        POLYGON, ///< Utilizado para representar o chão preenchido com polígonos sólidos.
        CUBE ///< Utilizado para representar o chão, teto e paredes feitos com linhas.
    };
};

#endif // UTILS_H
