<GameProjectFile>
  <PropertyGroup Type="Node" Name="AnimalMove1" ID="9b2712b8-9012-415f-a088-855627e4b972" Version="2.2.8.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="230" Speed="1.0000" ActivedAnimationName="reborn">
        <Timeline ActionTag="-2066128753" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="90" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="119" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="151" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="160" X="0.0000" Y="40.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="170" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="190" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="203" X="0.0000" Y="40.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="215" X="0.0000" Y="100.0000">
            <EasingData Type="1" />
          </PointFrame>
          <PointFrame FrameIndex="229" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="230" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-2066128753" Property="RotationSkew">
          <ScaleFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="10.0000" Y="10.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="90" X="-10.0000" Y="-10.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="119" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="151" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-2066128753" Property="Scale">
          <ScaleFrame FrameIndex="121" X="1.0000" Y="1.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="135" X="1.2000" Y="0.8000">
            <EasingData Type="26" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="149" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="151" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="180" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="189" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="190" X="1.0000" Y="0.0100">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="203" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-2066128753" Property="Alpha">
          <IntFrame FrameIndex="190" Value="255">
            <EasingData Type="0" />
          </IntFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="walk" StartIndex="1" EndIndex="120">
          <RenderColor A="255" R="0" G="100" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="drop" StartIndex="121" EndIndex="150">
          <RenderColor A="255" R="72" G="209" B="204" />
        </AnimationInfo>
        <AnimationInfo Name="battle" StartIndex="151" EndIndex="181">
          <RenderColor A="255" R="72" G="209" B="204" />
        </AnimationInfo>
        <AnimationInfo Name="reborn" StartIndex="190" EndIndex="240">
          <RenderColor A="255" R="165" G="42" B="42" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="16" ctype="GameNodeObjectData">
        <Size />
        <Children>
          <AbstractNodeData Name="image" ActionTag="-2066128753" Tag="8" IconVisible="False" LeftMargin="-200.0000" RightMargin="-200.0000" TopMargin="-400.0000" ctype="SpriteObjectData">
            <Size X="400.0000" Y="400.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="animal/ant.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>