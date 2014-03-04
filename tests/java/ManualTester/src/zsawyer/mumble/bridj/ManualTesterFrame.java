/* Copyright (C) 2013, zsawyer <zsawyer@users.sourceforge.net>

 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 - Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 - Neither the name of the Mumble Developers nor the names of its
 contributors may be used to endorse or promote products derived from this
 software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package zsawyer.mumble.bridj;

import zsawyer.mumble.LabledInput;
import java.awt.Color;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.FloatBuffer;
import java.util.HashMap;
import java.util.Map;
import javax.swing.GroupLayout;
import javax.swing.JLabel;
import org.bridj.Pointer;

/**
 *
 * @author zsawyer, 2013
 */
public class ManualTesterFrame extends javax.swing.JFrame {

	Map<String, LabledInput> inputs = new HashMap<>();

	/** Creates new form ManualTesterFrame */
	public ManualTesterFrame() {
		initComponents();
		initCustomComponents();
	}

	/** This method is called from within the constructor to
	 * initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is
	 * always regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        updateData = new javax.swing.JButton();
        updateName = new javax.swing.JButton();
        updateDescription = new javax.swing.JButton();
        updateIdentity = new javax.swing.JButton();
        updateContext = new javax.swing.JButton();
        updateVectors = new javax.swing.JButton();
        updateVectorsByAvatar = new javax.swing.JButton();
        initialize = new javax.swing.JButton();
        updateIdentityAndContext = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("ManualTester - BridJ");

        updateData.setText("data");
        updateData.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateDataActionPerformed(evt);
            }
        });

        updateName.setText("name");
        updateName.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateNameActionPerformed(evt);
            }
        });

        updateDescription.setText("descr");
        updateDescription.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateDescriptionActionPerformed(evt);
            }
        });

        updateIdentity.setText("indentity");
        updateIdentity.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateIdentityActionPerformed(evt);
            }
        });

        updateContext.setText("context");
        updateContext.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateContextActionPerformed(evt);
            }
        });

        updateVectors.setText("vectors");
        updateVectors.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateVectorsActionPerformed(evt);
            }
        });

        updateVectorsByAvatar.setText("vectorsByAvatar");
        updateVectorsByAvatar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateVectorsByAvatarActionPerformed(evt);
            }
        });

        initialize.setText("initialize");
        initialize.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                initializeActionPerformed(evt);
            }
        });

        updateIdentityAndContext.setText("both");
        updateIdentityAndContext.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateIdentityAndContextActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(updateVectors)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(updateVectorsByAvatar))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(updateIdentity)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(updateContext)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(updateIdentityAndContext))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(updateName)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(updateDescription))
                    .addComponent(updateData)
                    .addComponent(initialize))
                .addGap(0, 335, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(0, 313, Short.MAX_VALUE)
                .addComponent(initialize)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(updateName)
                    .addComponent(updateDescription))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(updateIdentity)
                    .addComponent(updateContext)
                    .addComponent(updateIdentityAndContext))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(updateVectors)
                    .addComponent(updateVectorsByAvatar))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(updateData))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void initializeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_initializeActionPerformed
		Pointer<Character> name = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_NAME_LENGTH, "name");

		Pointer<Character> description = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_DESCRIPTION_LENGTH, "description");

		int version;
		try {
			version = parseToInt("version");
		} catch (NumberFormatException e) {
			return;
		}

		LinkAPILibrary.initialize(name, description, version);
    }//GEN-LAST:event_initializeActionPerformed

    private void updateNameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateNameActionPerformed
		Pointer<Character> name = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_NAME_LENGTH, "name");
		LinkAPILibrary.commitName(name);
    }//GEN-LAST:event_updateNameActionPerformed

    private void updateDescriptionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateDescriptionActionPerformed
		Pointer<Character> description = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_DESCRIPTION_LENGTH, "description");
		LinkAPILibrary.commitDescription(description);
    }//GEN-LAST:event_updateDescriptionActionPerformed

    private void updateIdentityActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateIdentityActionPerformed
		Pointer<Character> identity = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_IDENTITY_LENGTH, "identity");
		LinkAPILibrary.commitIdentity(identity);
    }//GEN-LAST:event_updateIdentityActionPerformed

    private void updateContextActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateContextActionPerformed
		Pointer<Byte> context = parseToPointerByte(
				LinkAPILibrary.LINKAPI_MAX_CONTEXT_LENGTH, "context");
		int contextLength = inputs.get("context").getValue().length();
		LinkAPILibrary.commitContext(context, contextLength);
    }//GEN-LAST:event_updateContextActionPerformed

    private void updateVectorsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateVectorsActionPerformed
		try {
			Pointer<Float> avatarPosition = parseToFloatBuffer(
					"avatarPosition");
			Pointer<Float> avatarFront = parseToFloatBuffer("avatarFront");
			Pointer<Float> avatarTop = parseToFloatBuffer("avatarTop");

			Pointer<Float> cameraPosition = parseToFloatBuffer(
					"cameraPosition");
			Pointer<Float> cameraFront = parseToFloatBuffer("cameraFront");
			Pointer<Float> cameraTop = parseToFloatBuffer("cameraTop");

			LinkAPILibrary.commitVectors(avatarPosition, avatarFront,
					avatarTop,
					cameraPosition, cameraFront, cameraTop);
		} catch (NumberFormatException e) {
			return;
		}
    }//GEN-LAST:event_updateVectorsActionPerformed

    private void updateVectorsByAvatarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateVectorsByAvatarActionPerformed
		try {
			Pointer<Float> avatarPosition = parseToFloatBuffer(
					"avatarPosition");
			Pointer<Float> avatarFront = parseToFloatBuffer("avatarFront");
			Pointer<Float> avatarTop = parseToFloatBuffer("avatarTop");

			LinkAPILibrary.commitVectorsAvatarAsCamera(avatarPosition,
					avatarFront,
					avatarTop);
		} catch (NumberFormatException e) {
			return;
		}
    }//GEN-LAST:event_updateVectorsByAvatarActionPerformed

    private void updateDataActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateDataActionPerformed

		// TOFIX: this does not seem to work, only places empty values it seems

		LinkAPILibrary.LINKAPI_LINKED_MEMORY lm = new LinkAPILibrary.LINKAPI_LINKED_MEMORY();

		parseToPointerChar(LinkAPILibrary.LINKAPI_MAX_IDENTITY_LENGTH,
				"identity").setPointer(lm.identity());

		parseToPointerByte(LinkAPILibrary.LINKAPI_MAX_CONTEXT_LENGTH,
				"context").setPointer(lm.context());

		lm.contextLength(inputs.get("context").getValue().length());

		parseToPointerChar(LinkAPILibrary.LINKAPI_MAX_NAME_LENGTH,
				"name").setPointer(lm.name());

		parseToPointerChar(LinkAPILibrary.LINKAPI_MAX_DESCRIPTION_LENGTH,
				"description").setPointer(lm.description());

		try {
			lm.tick(parseToInt("tick"));
			lm.version(parseToInt("version"));

			parseToFloatBuffer("avatarPosition").setPointer(lm.
					avatarPosition());
			parseToFloatBuffer("avatarFront").setPointer(lm.avatarFront());
			parseToFloatBuffer("avatarTop").setPointer(lm.avatarTop());

			parseToFloatBuffer("cameraPosition").setPointer(lm.
					cameraPosition());
			parseToFloatBuffer("cameraFront").setPointer(lm.cameraFront());
			parseToFloatBuffer("cameraTop").setPointer(lm.cameraTop());
		} catch (NumberFormatException e) {
			return;
		}

		LinkAPILibrary.setData(Pointer.pointerTo(lm));

		inputs.get("tick").setValue(String.valueOf(parseToInt("tick") + 1));
    }//GEN-LAST:event_updateDataActionPerformed

    private void updateIdentityAndContextActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_updateIdentityAndContextActionPerformed
		Pointer<Character> identity = parseToPointerChar(
				LinkAPILibrary.LINKAPI_MAX_IDENTITY_LENGTH, "identity");
		Pointer<Byte> context = parseToPointerByte(
				LinkAPILibrary.LINKAPI_MAX_CONTEXT_LENGTH, "context");
		int contextLength = inputs.get("context").getValue().length();
		LinkAPILibrary.
				commitIdentityAndContext(identity, context, contextLength);
    }//GEN-LAST:event_updateIdentityAndContextActionPerformed

	/**
	 * @param args the command line arguments
	 */
	public static void main(String args[]) {
		/* Set the Nimbus look and feel */
		//<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
		 * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
		 */
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info
					: javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.
					getLogger(ManualTesterFrame.class.getName()).log(
							java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.
					getLogger(ManualTesterFrame.class.getName()).log(
							java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.
					getLogger(ManualTesterFrame.class.getName()).log(
							java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.
					getLogger(ManualTesterFrame.class.getName()).log(
							java.util.logging.Level.SEVERE, null, ex);
		}
		//</editor-fold>

		/* Create and display the form */
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				new ManualTesterFrame().setVisible(true);
			}
		});
	}
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton initialize;
    private javax.swing.JButton updateContext;
    private javax.swing.JButton updateData;
    private javax.swing.JButton updateDescription;
    private javax.swing.JButton updateIdentity;
    private javax.swing.JButton updateIdentityAndContext;
    private javax.swing.JButton updateName;
    private javax.swing.JButton updateVectors;
    private javax.swing.JButton updateVectorsByAvatar;
    // End of variables declaration//GEN-END:variables

	private void initCustomComponents() {
		this.inputs.put("version", new LabledInput("version", "2"));
		this.inputs.put("tick", new LabledInput("tick", "ignored"));

		this.inputs.put("avatarPosition", new LabledInput("avatarPosition",
				"1.0 1.1 1.2"));
		this.inputs.put("avatarFront", new LabledInput("avatarFront",
				"2.0 2.1 2.2"));
		this.inputs.put("avatarTop", new LabledInput("avatarTop",
				"3.0 3.1 3.2"));

		this.inputs.put("cameraPosition", new LabledInput("cameraPosition",
				"4.0 4.1 4.2"));
		this.inputs.put("cameraFront", new LabledInput("cameraFront",
				"5.0 5.1 5.2"));
		this.inputs.put("cameraTop", new LabledInput("cameraTop",
				"6.0 6.1 6.2"));

		this.inputs.
				put("name", new LabledInput("name", "ManualTester w/ BridJ"));
		this.inputs.put("description", new LabledInput("description",
				"ManualTester tests the LinkAPI library"));

		this.inputs.put("identity", new LabledInput("identity",
				"zsawyer_development"));
		this.inputs.put("context", new LabledInput("context",
				"ManualTester_development"));

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
				getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(addAllInputs(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.
						createSequentialGroup()
						.addContainerGap()))
				.addGroup(layout.createSequentialGroup()
						.addGroup(layout.createParallelGroup(
										javax.swing.GroupLayout.Alignment.LEADING).
								addGroup(layout.createSequentialGroup()
										.addComponent(updateVectors)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED).
										addComponent(updateVectorsByAvatar))
								.addGroup(layout.createSequentialGroup()
										.addComponent(updateIdentity)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED).
										addComponent(updateContext)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED).
										addComponent(updateIdentityAndContext))
								.addGroup(layout.createSequentialGroup()
										.addComponent(updateName)
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED).
										addComponent(updateDescription))
								.addComponent(updateData)
								.addComponent(initialize))
						.addGap(0, 358, Short.MAX_VALUE)));

		layout.setVerticalGroup(addAllInputs(
				layout.createSequentialGroup())
				.addGroup(layout.createSequentialGroup()
						.addComponent(initialize)
						.addPreferredGap(
								javax.swing.LayoutStyle.ComponentPlacement.RELATED).
						addGroup(layout.createParallelGroup(
										javax.swing.GroupLayout.Alignment.BASELINE).
								addComponent(updateName)
								.addComponent(updateDescription))
						.addPreferredGap(
								javax.swing.LayoutStyle.ComponentPlacement.RELATED).
						addGroup(layout.createParallelGroup(
										javax.swing.GroupLayout.Alignment.BASELINE).
								addComponent(updateIdentity)
								.addComponent(updateContext)
								.addComponent(updateIdentityAndContext))
						.addPreferredGap(
								javax.swing.LayoutStyle.ComponentPlacement.RELATED).
						addGroup(layout.createParallelGroup(
										javax.swing.GroupLayout.Alignment.BASELINE).
								addComponent(updateVectors)
								.addComponent(updateVectorsByAvatar))
						.addPreferredGap(
								javax.swing.LayoutStyle.ComponentPlacement.RELATED).
						addComponent(updateData)));
		pack();
	}

	private GroupLayout.Group addAllInputs(GroupLayout.Group baseGroup) {
		for (Map.Entry<String, LabledInput> entry : inputs.entrySet()) {
			String label = entry.getKey();
			LabledInput input = entry.getValue();

			baseGroup.addComponent(input);
		}

		return baseGroup;
	}

	private Pointer<Float> parseToFloatBuffer(String labelName) throws
			NumberFormatException {
		LabledInput input = inputs.get(labelName);
		Pointer<Float> pointer = Pointer.allocateFloats(3);
		try {
			String[] split = input.getValue().split(" ");
			for (int i = 0; i < split.length; i++) {
				String string = split[i];
				pointer.set(i, Float.parseFloat(string));
			}
		} catch (NumberFormatException | IndexOutOfBoundsException e) {
			JLabel label = input.getLabel();
			label.setForeground(Color.red);
		}
		return pointer;
	}

	private Pointer<Character> parseToPointerChar(int capacity, String label) {
		Pointer<Character> pointer = Pointer.allocateChars(capacity);
		pointer.setArray(inputs.get(label).getValue().toCharArray());
		return pointer;
	}

	private Pointer<Byte> parseToPointerByte(int capacity, String label) {
		Pointer<Byte> pointer = Pointer.allocateBytes(capacity);
		pointer.setBytes(inputs.get(label).getValue().getBytes());
		return pointer;
	}

	private int parseToInt(String labelName) throws NumberFormatException {
		LabledInput input = inputs.get(labelName);
		try {
			return Integer.parseInt(input.getValue());
		} catch (NumberFormatException e) {
			JLabel label = input.getLabel();
			label.setForeground(Color.red);
			throw e;
		}
	}
}
